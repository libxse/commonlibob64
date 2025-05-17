#pragma once

#include "UE/E/ESPMode.h"
#include "UE/T/TTemplate.h"

namespace UE
{
	template <class T, ESPMode>
	class TSharedFromThis;

	template <class T, ESPMode>
	class TSharedPtr;
}

namespace UE::SharedPointerInternals
{
	template <ESPMode>
	class FWeakReferencer;

	struct FNullTag
	{};

	template <ESPMode M>
	class TReferenceControllerBase
	{
		using RefCountType = std::conditional_t<M == ESPMode::ThreadSafe, std::atomic<std::int32_t>, std::int32_t>;

	public:
		explicit TReferenceControllerBase() = default;

		TReferenceControllerBase(const TReferenceControllerBase&) = delete;
		TReferenceControllerBase& operator=(const TReferenceControllerBase&) = delete;

		// add
		virtual void DestroyObject() = 0;       // 00
		virtual ~TReferenceControllerBase() {}  // 01

		void AddSharedReference()
		{
			if constexpr (M == ESPMode::ThreadSafe)
				++sharedReferenceCount;
			else
				++sharedReferenceCount;
		}

		void AddWeakReference()
		{
			if constexpr (M == ESPMode::ThreadSafe)
				++weakReferenceCount;
			else
				++weakReferenceCount;
		}

		bool ConditionallyAddSharedReference()
		{
			if constexpr (M == ESPMode::ThreadSafe) {
				std::int32_t original = sharedReferenceCount.load(std::memory_order_relaxed);

				for (;;) {
					if (original == 0)
						return false;

					if (sharedReferenceCount.compare_exchange_weak(original, original + 1, std::memory_order_relaxed))
						return true;
				}
			} else {
				if (sharedReferenceCount == 0)
					return false;

				++sharedReferenceCount;
				return true;
			}
		}

		std::int32_t GetSharedReferenceCount() const
		{
			if constexpr (M == ESPMode::ThreadSafe)
				return sharedReferenceCount.load(std::memory_order_relaxed);
			else
				return sharedReferenceCount;
		}

		bool IsUnique() const
		{
			if constexpr (M == ESPMode::ThreadSafe)
				return sharedReferenceCount.load(std::memory_order_acquire) == 1;
			else
				return sharedReferenceCount == 1;
		}

		void ReleaseSharedReference()
		{
			if constexpr (M == ESPMode::ThreadSafe) {
				std::int32_t old = sharedReferenceCount.fetch_sub(1, std::memory_order_acq_rel);

				assert(old > 0);

				if (old == 1) {
					DestroyObject();
					ReleaseWeakReference();
				}
			} else {
				assert(sharedReferenceCount > 0);

				if (--sharedReferenceCount == 0) {
					DestroyObject();
					ReleaseWeakReference();
				}
			}
		}

		void ReleaseWeakReference()
		{
			if constexpr (M == ESPMode::ThreadSafe) {
				std::int32_t old = weakReferenceCount.fetch_sub(1, std::memory_order_acq_rel);

				assert(old > 0);

				if (old == 1)
					delete this;
			} else {
				assert(weakReferenceCount > 0);

				if (--weakReferenceCount == 0)
					delete this;
			}
		}

	public:
		// members
		RefCountType sharedReferenceCount{ 1 };
		RefCountType weakReferenceCount{ 1 };
	};
	static_assert(sizeof(TReferenceControllerBase<ESPMode::NotThreadSafe>) == 0x10);
	static_assert(sizeof(TReferenceControllerBase<ESPMode::ThreadSafe>) == 0x10);

	template <ESPMode M>
	class FSharedReferencer
	{
		template <ESPMode>
		friend class FWeakReferencer;

	public:
		FSharedReferencer() = default;

		explicit FSharedReferencer(TReferenceControllerBase<M>* a_controller) :
			referenceController(a_controller)
		{}

		FSharedReferencer(FSharedReferencer&& a_other) :
			referenceController(a_other.referenceController)
		{
			a_other.referenceController = nullptr;
		}

		FSharedReferencer(const FSharedReferencer& a_other) :
			referenceController(a_other.referenceController)
		{
			if (referenceController)
				referenceController->AddSharedReference();
		}

		FSharedReferencer(const FWeakReferencer<M>& a_weakReferencer) :
			referenceController(a_weakReferencer.referenceController)
		{
			if (referenceController)
				if (!referenceController->ConditionallyAddSharedReference())
					referenceController = nullptr;
		}

		FSharedReferencer(FWeakReferencer<M>&& a_weakReferencer) :
			referenceController(a_weakReferencer.referenceController)
		{
			if (referenceController) {
				if (!referenceController->ConditionallyAddSharedReference())
					referenceController = nullptr;

				a_weakReferencer.referenceController->ReleaseWeakReference();
				a_weakReferencer.referenceController = nullptr;
			}
		}

		~FSharedReferencer()
		{
			if (referenceController)
				referenceController->ReleaseSharedReference();
		}

		FSharedReferencer& operator=(const FSharedReferencer& a_other)
		{
			auto newReferenceController = a_other.referenceController;
			if (newReferenceController != referenceController) {
				if (newReferenceController)
					newReferenceController->AddSharedReference();

				if (referenceController) 
					referenceController->ReleaseSharedReference();

				referenceController = newReferenceController;
			}

			return *this;
		}

		FSharedReferencer& operator=(FSharedReferencer&& a_other)
		{
			auto newReferenceController = a_other.referenceController;
			auto oldReferenceController = referenceController;
			if (newReferenceController != oldReferenceController) {
				a_other.referenceController = nullptr;
				referenceController = newReferenceController;

				if (oldReferenceController)
					oldReferenceController->ReleaseSharedReference();
			}

			return *this;
		}

		const std::int32_t GetSharedReferenceCount() const
		{
			return referenceController ? referenceController->GetSharedReferenceCount() : 0;
		}

		const bool IsUnique() const
		{
			return referenceController && referenceController->IsUnique();
		}

		const bool IsValid() const
		{
			return referenceController;
		}

	private:
		// members
		TReferenceControllerBase<M>* referenceController{ nullptr };  // 00
	};
	static_assert(sizeof(FSharedReferencer<ESPMode::ThreadSafe>) == 0x08);

	template <ESPMode M>
	class FWeakReferencer
	{
		template <ESPMode>
		friend class FSharedReferencer;

	public:
		FWeakReferencer() = default;

		FWeakReferencer(const FWeakReferencer& a_other) :
			referenceController(a_other.referenceController)
		{
			if (referenceController)
				referenceController->AddWeakReference();
		}

		FWeakReferencer(FWeakReferencer&& a_other) :
			referenceController(a_other.referenceController)
		{
			a_other.referenceController = nullptr;
		}

		FWeakReferencer(const FSharedReferencer<M>& a_sharedReferencer) :
			referenceController(a_sharedReferencer.referenceController)
		{
			if (referenceController) 
				referenceController->AddWeakReference();
		}

		~FWeakReferencer()
		{
			if (referenceController)
				referenceController->ReleaseWeakReference();
		}

		FWeakReferencer& operator=(const FWeakReferencer& a_other)
		{
			AssignReferenceController(a_other.referenceController);

			return *this;
		}

		FWeakReferencer& operator=(FWeakReferencer&& a_other)
		{
			auto oldReferenceController = referenceController;
			referenceController = a_other.referenceController;
			a_other.referenceController = nullptr;

			if (oldReferenceController)
				oldReferenceController->ReleaseWeakReference();

			return *this;
		}

		FWeakReferencer& operator=(const FSharedReferencer<M>& a_sharedReferencer)
		{
			AssignReferenceController(a_sharedReferencer.referenceController);

			return *this;
		}

		const bool IsValid() const
		{
			return referenceController && referenceController->GetSharedReferenceCount() > 0;
		}

	private:
		void AssignReferenceController(TReferenceControllerBase<M>* a_controller)
		{
			if (a_controller != referenceController) {
				if (a_controller)
					a_controller->AddWeakReference();

				if (referenceController)
					referenceController->ReleaseWeakReference();

				referenceController = a_controller;
			}
		}

	private:
		// members
		TReferenceControllerBase<M>* referenceController{ nullptr };  // 00
	};
	static_assert(sizeof(FWeakReferencer<ESPMode::ThreadSafe>) == 0x08);

	template <class D, bool = std::is_empty_v<D>>
	class TDeleterHolder :
		private D
	{
	public:
		explicit TDeleterHolder(D&& a_other) :
			D(MoveTemp(a_other))
		{
		}

		template <class T>
		void InvokeDeleter(T* a_object)
		{
			Invoke(*static_cast<D*>(this), a_object);
		}
	};

	template <class D>
	class TDeleterHolder<D, false>
	{
	public:
		explicit TDeleterHolder(D&& a_other) :
			D(MoveTemp(a_other))
		{
		}

		template <class T>
		void InvokeDeleter(T* a_object)
		{
			Invoke(deleter, a_object);
		}

	private:
		D deleter;
	};

	template <class T, class D, ESPMode M>
	class TReferenceControllerWithDeleter :
		private TDeleterHolder<D>,
		public TReferenceControllerBase<M>
	{
	public:
		explicit TReferenceControllerWithDeleter(T* a_object, D&& a_deleter) :
			TDeleterHolder<D>(MoveTemp(a_deleter)), object(a_object)
		{}

		TReferenceControllerWithDeleter(const TReferenceControllerWithDeleter&) = delete;
		TReferenceControllerWithDeleter& operator=(const TReferenceControllerWithDeleter&) = delete;

		virtual void DestroyObject() override
		{
			this->InvokeDeleter(object);
		}

	private:
		// members
		T* object;  // 00
	};

	template <class T1, class T2, class T3, ESPMode M>
	void EnableSharedFromThis(const TSharedPtr<T1, M>* a_sharedPtr, const T2* a_object, const TSharedFromThis<T3, M>* a_shared)
	{
		if (a_shared)
			a_shared->UpdateWeakReferenceInternal(a_sharedPtr, const_cast<T2*>(a_object));
	}

	template <class T>
	struct DefaultDeleter
	{
		static void operator()(T* a_object)
		{
			delete a_object;
		}
	};

	template <ESPMode M, class T>
	inline TReferenceControllerBase<M>* NewDefaultReferenceController(T* a_object)
	{
		return new TReferenceControllerWithDeleter<T, DefaultDeleter<T>, M>(a_object, DefaultDeleter<T>());
	}
}
