#pragma once

namespace UE
{
	template <class T>
	struct TAllocatorTraitsBase
	{
		static constexpr bool IsZeroConstruct{ false };
		static constexpr bool SupportsFreezeMemoryImage{ false };
		static constexpr bool SupportsElementAlignment{ false };
	};

	template <class T>
	struct TAllocatorTraits :
		TAllocatorTraitsBase<T>
	{};
}
