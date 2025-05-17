#pragma once

#include "UE/F/FDefaultAllocator.h"
#include "UE/T/TChooseClass.h"
#include "UE/T/TTemplate.h"

namespace UE
{
	template <class T, class A = FDefaultAllocator>
	class TArray
	{
	public:
		using SizeType = A::SizeType;
		using ElementAllocatorType = TChooseClass<
			A::NeedsElementType, typename A::template ForElementType<T>, typename A::ForAnyElementType>::Result;

		TArray() :
			arrayMax(allocatorInstance.GetInitialCapacity())
		{}

		TArray(const TArray& a_other)
		{
			CopyToEmpty(a_other.GetData(), a_other.Num(), 0);
		}

		TArray(std::initializer_list<T> a_init)
		{
			CopyToEmpty(a_init.begin(), (SizeType)a_init.size(), 0);
		}

		TArray(const T* a_ptr, SizeType a_count)
		{
			assert(a_ptr != nullptr || a_count == 0);

			CopyToEmpty(a_ptr, a_count, 0);
		}

		T* GetData()
		{
			return (T*)allocatorInstance.GetAllocation();
		}

		const T* GetData() const
		{
			return (const T*)allocatorInstance.GetAllocation();
		}

		bool IsEmpty() const
		{
			return arrayNum == 0;
		}

		SizeType Num() const
		{
			return arrayNum;
		}

		SizeType Max() const
		{
			return arrayMax;
		}

		T& operator[](SizeType a_index)
		{
			return GetData()[a_index];
		}

		const T& operator[](SizeType a_index) const
		{
			return GetData()[a_index];
		}

		T*       begin() { return GetData(); }
		const T* begin() const { return GetData(); }
		T*       end() { return GetData() + Num(); }
		const T* end() const { return GetData() + Num(); }

		SizeType AllocatorCalculateSlackReserve(SizeType a_newMax)
		{
			if constexpr (TAllocatorTraits<A>::SupportsElementAlignment) {
				return allocatorInstance.CalculateSlackReserve(a_newMax, sizeof(T), alignof(T));
			} else {
				return allocatorInstance.CalculateSlackReserve(a_newMax, sizeof(T));
			}
		}

		void AllocatorResizeAllocation(SizeType a_current, SizeType a_new)
		{
			if constexpr (TAllocatorTraits<A>::SupportsElementAlignment) {
				allocatorInstance.ResizeAllocation(a_current, a_new, sizeof(T), alignof(T));
			} else {
				allocatorInstance.ResizeAllocation(a_current, a_new, sizeof(T));
			}
		}

		template <class U, class S>
		void CopyToEmpty(const U* a_data, S a_count, SizeType a_prevMax)
		{
			arrayNum = static_cast<SizeType>(a_count);
			if (a_count || a_prevMax) {
				ResizeForCopy(arrayNum, a_prevMax);
				ConstructItems<U>(GetData(), a_data, a_count);
			} else {
				arrayMax = allocatorInstance.GetInitialCapacity();
			}
		}

		void ResizeForCopy(SizeType a_newMax, SizeType a_prevMax)
		{
			if (a_newMax)
				a_newMax = AllocatorCalculateSlackReserve(a_newMax);

			if (a_newMax > a_prevMax) {
				AllocatorResizeAllocation(0, a_newMax);
				arrayMax = a_newMax;
			} else {
				arrayMax = a_prevMax;
			}
		}

		// members
		ElementAllocatorType allocatorInstance;  // 00
		std::int32_t         arrayNum{ 0 };      // 08
		std::int32_t         arrayMax;           // 0C
	};
	static_assert(sizeof(TArray<wchar_t>) == 0x10);
}
