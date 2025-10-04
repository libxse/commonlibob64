#pragma once

#include "UE/F/FMath.h"
#include "UE/T/TAlignedBytes.h"
#include "UE/T/TSizedHeapAllocator.h"

namespace UE
{
	using FAlignedInlineDelegateType = TAlignedBytes<16, 16>;
	using FDelegateAllocatorType = FHeapAllocator;

	class UObject;

	template <class M>
	class TDelegateBase :
		public TDelegateAccessHandlerBase<M>
	{
		using Super = TDelegateAccessHandlerBase<M>;

		template <class>
		friend class TMulticastDelegateBase;

	protected:
		explicit TDelegateBase() = default;

	public:
		~TDelegateBase()
		{
			Unbind();
		}

		void Unbind()
		{
			const auto scope = Super::GetWriteAccessScope();

			UnbindUnchecked();
		}

		bool IsBound() const
		{
			const auto scope = Super::GetReadAccessScope();
			const auto instance = GetDelegateInstanceProtected();
			return instance && instance->IsSafeToExecute();
		}

		UObject* GetUObject() const
		{
			const auto scope = Super::GetReadAccessScope();
			const auto instance = GetDelegateInstanceProtected();
			return instance ? instance->GetUObject() : nullptr;
		}

	protected:
		template <class T, class... A>
		void CreateDelegateInstance(A&&... a_args)
		{
			const auto scope = Super::GetWriteAccessScope();
			if (auto instance = GetDelegateInstanceProtected()) {
				instance->~IDelegateInstance();
			}

			new (Allocate(sizeof(T))) T(std::forward<A>(a_args)...);
		}

		IDelegateInstance* GetDelegateInstanceProtected()
		{
			return m_delegateSize ? reinterpret_cast<IDelegateInstance*>(m_delegateAllocator.GetAllocation()) : nullptr;
		}

		const IDelegateInstance* GetDelegateInstanceProtected() const
		{
			return m_delegateSize ? reinterpret_cast<const IDelegateInstance*>(m_delegateAllocator.GetAllocation()) : nullptr;
		}

	private:
		void* Allocate(std::int32_t a_size)
		{
			std::int32_t size = FMath::DivideAndRoundUp(a_size, static_cast<std::int32_t>(sizeof(FAlignedInlineDelegateType)));
			if (m_delegateSize != size) {
				m_delegateAllocator.ResizeAllocation(0, size, sizeof(FAlignedInlineDelegateType));
				m_delegateSize = size;
			}

			return m_delegateAllocator.GetAllocation();
		}

		void UnbindUnchecked()
		{
			if (auto instance = GetDelegateInstanceProtected()) {
				instance->~IDelegateInstance();
				m_delegateAllocator.ResizeAllocation(0, 0, sizeof(FAlignedInlineDelegateType));
				m_delegateSize = 0;
			}
		}

	private:
		// members
		FDelegateAllocatorType::ForElementType<FAlignedInlineDelegateType> m_delegateAllocator;
		std::int32_t                                                       m_delegateSize{ 0 };
	};
}
