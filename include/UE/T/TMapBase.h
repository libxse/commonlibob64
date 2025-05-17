#pragma once

#include "UE/F/FPathGridPointDataArray.h"
#include "UE/T/TDefaultMapHashableKeyFuncs.h"
#include "UE/T/TPair.h"
#include "UE/T/TSet.h"

namespace UE
{
	template <class K, class V, class A, class H>
	class TMapBase
	{
	public:
		// members
		TSet<TPair<K, V>, H, A> pairs;  // 00
	};
	static_assert(sizeof(TMapBase<void*, FPathGridPointDataArray, FDefaultSetAllocator, TDefaultMapHashableKeyFuncs<void*, void*, 0>>) == 0x50);
}
