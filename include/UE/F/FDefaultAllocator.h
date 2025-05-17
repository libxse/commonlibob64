#pragma once

#include "UE/T/TSizedDefaultAllocator.h"

namespace UE
{
	using FDefaultAllocator = TSizedDefaultAllocator<32>;
	using FDefaultAllocator64 = TSizedDefaultAllocator<64>;

	template <>
	struct TAllocatorTraits<FDefaultAllocator> :
		TAllocatorTraits<typename FDefaultAllocator::Super>
	{};

	template <>
	struct TAllocatorTraits<FDefaultAllocator64> :
		TAllocatorTraits<typename FDefaultAllocator64::Super>
	{};
}
