#pragma once

#include "UE/T/TSizedHeapAllocator.h"

namespace UE
{
	class FMemory;

	template <std::int32_t N>
	class TSizedDefaultAllocator :
		public TSizedHeapAllocator<N>
	{
	public:
		using Super = TSizedHeapAllocator<N>;
	};
	static_assert(std::is_empty_v<TSizedDefaultAllocator<32>>);

	template <std::int32_t N>
	struct TAllocatorTraits<TSizedDefaultAllocator<N>> :
		TAllocatorTraits<typename TSizedDefaultAllocator<N>::Super>
	{};
}
