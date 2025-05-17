#pragma once

#include "UE/F/FDefaultBitArrayAllocator.h"
#include "UE/F/FDefaultSparseArrayAllocator.h"
#include "UE/T/TAlignedBytes.h"
#include "UE/T/TArray.h"
#include "UE/T/TBitArray.h"
#include "UE/T/TSparseArrayElementOrFreeListLink.h"

namespace UE
{
	template <class T, class A = FDefaultSparseArrayAllocator>
	class TSparseArray
	{
	public:
		using FElementOrFreeListLink = TSparseArrayElementOrFreeListLink<TAlignedBytes<sizeof(T), alignof(T)>>;
		using DataType = TArray<FElementOrFreeListLink, typename A::ElementAllocator>;
		using AllocationBitArrayType = TBitArray<typename A::BitArrayAllocator>;

		T& operator[](std::int32_t a_index)
		{
			return *(T*)&((FElementOrFreeListLink*)data.GetData())[a_index].elementData;
		}

		const T& operator[](std::int32_t a_index) const
		{
			return *(T*)&((FElementOrFreeListLink*)data.GetData())[a_index].elementData;
		}

		// members
		DataType               data;             // 00
		AllocationBitArrayType allocationFlags;  // 10
		std::int32_t           firstFreeIndex;   // 30
		std::int32_t           numFreeIndices;   // 34
	};
	static_assert(sizeof(TSparseArray<void*>) == 0x38);
}
