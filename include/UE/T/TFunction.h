#pragma once

#include "UE/T/TAlignedBytes.h"
#include "UE/T/TTypeTraits.h"

namespace UE::Core::Private::Function
{
	template <class F, class R, class... T>
	struct TFunctorReturnTypeIsCompatible
	{
		static constexpr bool Value{ std::is_constructible_v<R, decltype(std::declval<F>()(std::declval<T>()...))> }; 
	};

	template <class MR, class C, class R, class... T>
	struct TFunctorReturnTypeIsCompatible<MR C::*, R, T...>
	{
		static constexpr bool Value{ std::is_constructible_v<R, MR> };
	};

	template <class MR, class C, class R, class... T>
	struct TFunctorReturnTypeIsCompatible<MR C::* const, R, T...>
	{
		static constexpr bool Value{ std::is_constructible_v<R, MR> };
	};

	template <class MR, class C, class... MT, class R, class... T>
	struct TFunctorReturnTypeIsCompatible<MR (C::*)(MT...), R, T...>
	{
		static constexpr bool Value{ std::is_constructible_v<R, MR> };
	};

	template <class MR, class C, class... MT, class R, class... T>
	struct TFunctorReturnTypeIsCompatible<MR (C::*)(MT...) const, R, T...>
	{
		static constexpr bool Value{ std::is_constructible_v<R, MR> };
	};

	template <class T, class F>
	struct TFuncCanBindToFunctor;

	template <class F, class R, class... T>
	struct TFuncCanBindToFunctor<R(T...), F>
	{
		static constexpr bool Value{ std::is_invocable_v<F, T...> && TFunctorReturnTypeIsCompatible<F, R, T...>::Value };
	};

	template <class F, class... T>
	struct TFuncCanBindToFunctor<void(T...), F>
	{
		static constexpr bool Value{ std::is_invocable_v<F, T...> };
	};
}

namespace UE::Core::Private::Function
{
	template <bool>
	class TFunctionStorage;

	class IFunction_OwnedObject
	{
	public:
		virtual void* CloneToEmptyStorage(void* a_storage) const = 0;  // 00
		virtual void* GetAddress() = 0;                                // 01
		virtual void  Destroy() = 0;                                   // 02
		virtual ~IFunction_OwnedObject() = default;                    // 03
	};
	static_assert(sizeof(IFunction_OwnedObject) == 0x8);

	template <class T>
	class IFunction_OwnedObject_OnHeap :
		public IFunction_OwnedObject
	{
	public:
		virtual void Destroy() override
		{
			void* thisPtr = this;
			this->~IFunction_OwnedObject_OnHeap();
			FMemory::Free(thisPtr);
		}
	};
	static_assert(sizeof(IFunction_OwnedObject_OnHeap<void>) == 0x8);

	template <class T>
	class IFunction_OwnedObject_Inline :
		public IFunction_OwnedObject
	{
	public:
		virtual void Destroy() override
		{
			this->~IFunction_OwnedObject_Inline();
		}
	};
	static_assert(sizeof(IFunction_OwnedObject_Inline<void>) == 0x8);

	template <class T, bool H>
	struct TFunction_OwnedObject :
		public TChooseClass<H, IFunction_OwnedObject_OnHeap<T>, IFunction_OwnedObject_Inline<T>>::Result
	{
		template <class... U>
		explicit TFunction_OwnedObject(U&&... a_args) :
			object(std::forward<U>(a_args)...)
		{
		}

		virtual void* GetAddress() override
		{
			return &object;
		}

		// members
		T object;  // 08
	};

	template <class T, bool H>
	class TFunction_CopyableOwnedObject :
		public TFunction_OwnedObject<T, H>
	{
	public:
		explicit TFunction_CopyableOwnedObject(const T& a_object) :
			TFunction_OwnedObject<T, H>(a_object)
		{}

		explicit TFunction_CopyableOwnedObject(T&& a_object) :
			TFunction_OwnedObject<T, H>(MoveTemp(a_object))
		{}

		virtual void* CloneToEmptyStorage(void* a_storage) const override;
	};

	template <class T, bool H>
	class TFunction_UniqueOwnedObject :
		public TFunction_OwnedObject<T, H>
	{
	public:
		explicit TFunction_UniqueOwnedObject(T&& a_object) :
			TFunction_OwnedObject<T, H>(MoveTemp(a_object))
		{}

		virtual void* CloneToEmptyStorage(void* a_storage) const override
		{
			assert(false);
			return nullptr;
		}
	};

	template <class F, class... T>
	auto Invoke(F&& Func, T&&... a_args)
		-> decltype(std::forward<F>(Func)(std::forward<T>(a_args)...))
	{
		return std::forward<F>(Func)(std::forward<T>(a_args)...);
	}

	template <class F, class R, class... T>
	struct TFunctionRefCaller
	{
		static R Call(void* a_object, T&... a_params)
		{
			if constexpr (std::is_void_v<R>)
				Invoke(*(F*)a_object, std::forward<T>(a_params)...);
			else
				return Invoke(*(F*)a_object, std::forward<T>(a_params)...);
		}
	};

	template <typename T, bool U, bool H>
	struct TStorageOwnerType;

	template <typename T, bool H>
	struct TStorageOwnerType<T, true, H>
	{
		using Type = TFunction_UniqueOwnedObject<typename std::decay_t<T>, H>;
	};

	template <typename T, bool H>
	struct TStorageOwnerType<T, false, H>
	{
		using Type = TFunction_CopyableOwnedObject<typename std::decay_t<T>, H>;
	};

	template <typename T, bool U, bool H>
	using TStorageOwnerTypeT = typename TStorageOwnerType<T, U, H>::Type;

	template <class T>
	bool IsBound(const T& a_func)
	{
		if constexpr (std::is_pointer_v<T> || std::is_member_pointer_v<T> || TIsTFunction<T>::Value)
			return !!a_func;
		else
			return true;
	}

	class FFunctionStorage
	{
	public:
		static constexpr bool NULLABLE{ true };

		FFunctionStorage() = default;

		FFunctionStorage(FFunctionStorage&& a_other) :
			heapAllocation(a_other.heapAllocation)
		{
			a_other.heapAllocation = nullptr;
			FMemory::Memcpy(&inlineAllocation, &a_other.inlineAllocation, sizeof(inlineAllocation));
		}

		void* BindCopy(const FFunctionStorage& a_other)
		{
			return a_other.GetBoundObject()->CloneToEmptyStorage(this);
		}

		IFunction_OwnedObject* GetBoundObject() const
		{
			if (auto ptr = static_cast<IFunction_OwnedObject*>(heapAllocation))
				return ptr;

			auto ptr = reinterpret_cast<const IFunction_OwnedObject*>(&inlineAllocation);
			return const_cast<IFunction_OwnedObject*>(ptr);
		}

		void* GetPtr() const
		{
			return GetBoundObject()->GetAddress();
		}

		void Unbind()
		{
			GetBoundObject()->Destroy();
		}

		// members
		void*                 heapAllocation{ nullptr };
		TAlignedBytes<32, 16> inlineAllocation;
	};
	static_assert(sizeof(FFunctionStorage) == 0x030);

	template <bool U>
	class TFunctionStorage :
		public FFunctionStorage
	{
	public:
		TFunctionStorage() = default;

		TFunctionStorage(FFunctionStorage&& a_other) :
			FFunctionStorage(MoveTemp(a_other))
		{}

		template <class T>
		std::decay_t<T>* Bind(T&& a_func)
		{
			constexpr bool inlined = sizeof(TStorageOwnerTypeT<T, U, false>) <= 32;
			using OwnedType = TStorageOwnerTypeT<T, U, !inlined>;

			if (!IsBound(a_func))
				return nullptr;

			void* ptr;
			if constexpr (inlined) {
				ptr = &inlineAllocation;
			} else {
				ptr = FMemory::Malloc(sizeof(OwnedType), alignof(OwnedType));
				heapAllocation = ptr;
			}

			auto mem = new (ptr) OwnedType(std::forward<T>(a_func));
			return &mem->object;
		}
	};

	template <class T, bool H>
	void* TFunction_CopyableOwnedObject<T, H>::CloneToEmptyStorage(void* a_storage) const
	{
		auto& storage = *(TFunctionStorage<false>*)a_storage;

		void* ptr;
		if (!H) {
			ptr = &storage.inlineAllocation;
		} else {
			ptr = FMemory::Malloc(sizeof(TFunction_CopyableOwnedObject), alignof(TFunction_CopyableOwnedObject));
			storage.heapAllocation = ptr;
		}

		auto mem = new (ptr) TFunction_CopyableOwnedObject(this->object);
		return &mem->object;
	}

	template <class S, class T>
	class TFunctionRefBase;

	template <class S, class R, class... T>
	class TFunctionRefBase<S, R(T...)>
	{
	public:
		TFunctionRefBase() = default;

		TFunctionRefBase(TFunctionRefBase&& a_other) :
			callable(a_other.callable), storage(MoveTemp(a_other.storage))
		{
			if constexpr (S::NULLABLE)
				if (!callable)
					return;

			if (callable)
				a_other.callable = nullptr;
		}

		template <class U>
		TFunctionRefBase(TFunctionRefBase<U, R(T...)>&& a_other) :
			callable(a_other.callable), storage(MoveTemp(a_other.storage))
		{
			if (callable)
				a_other.callable = nullptr;
		}

		template <class U>
		TFunctionRefBase(const TFunctionRefBase<U, R(T...)>& a_other) :
			callable(a_other.callable)
		{
			if constexpr (U::NULLABLE)
				if (!callable)
					return;

			storage.BindCopy(a_other.storage);
		}

		TFunctionRefBase(const TFunctionRefBase& a_other) :
			callable(a_other.callable)
		{
			if constexpr (S::NULLABLE)
				if (!callable)
					return;

			storage.BindCopy(a_other.storage);
		}

		template <class U>
		requires(!std::is_same_v<TFunctionRefBase, std::decay_t<U>>)
		TFunctionRefBase(U&& a_func)
		{
			auto binding = storage.Bind(std::forward<U>(a_func));
			if constexpr (S::NULLABLE)
				if (!binding)
					return;

			callable = &TFunctionRefCaller<std::remove_pointer_t<decltype(binding)>, R, T...>::Call;
		}

		~TFunctionRefBase()
		{
			if constexpr (S::NULLABLE) {
				if (!callable)
					return;
			}

			storage.Unbind();
		}

		bool IsSet() const
		{
			return !!callable;
		}

		void Reset()
		{
			if (callable) {
				storage.Unbind();
				callable = nullptr;
			}
		}

		// members
		R (*callable)
		(void*, T&...){ nullptr };
		S storage;
	};
}

namespace UE
{
	template <class T>
	class TFunction :
		public Core::Private::Function::TFunctionRefBase<Core::Private::Function::TFunctionStorage<false>, T>
	{
	public:
		TFunction() = default;
	};
}
