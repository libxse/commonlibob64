#pragma once

#include "UE/D/DefaultKeyFuncs.h"
#include "UE/F/FDefaultSetAllocator.h"
#include "UE/T/TSetElement.h"
#include "UE/T/TSparseArray.h"

namespace UE
{
	template <class T, class KeyFuncs = DefaultKeyFuncs<T>, class A = FDefaultSetAllocator>
	class TSet
	{
	public:
		using SetElementType = TSetElement<T>;
		using ElementArrayType = TSparseArray<SetElementType, typename A::SparseArrayAllocator>;
		using HashType = typename A::HashAllocator::template ForElementType<FSetElementId>;

		TSet() = default;

		T& Get(FSetElementId a_id)
		{
			return elements[a_id.index].value;
		}

		const T& Get(FSetElementId a_id) const
		{
			return elements[a_id.index].value;
		}

		T& operator[](FSetElementId a_id)
		{
			return elements[a_id.index].value;
		}

		const T& operator[](FSetElementId a_id) const
		{
			return elements[a_id.index].value;
		}

		// members
		ElementArrayType     elements;       // 00
		mutable HashType     hash;           // 38
		mutable std::int32_t hashSize{ 0 };  // 48
	};
	static_assert(sizeof(TSet<void*>) == 0x50);
}
