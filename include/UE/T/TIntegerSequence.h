#pragma once

namespace UE
{
	template <class T, T... I>
	struct TIntegerSequence
	{};
	static_assert(std::is_empty_v<TIntegerSequence<std::uint32_t, 0>>);

	template <class T, T N>
	using TMakeIntegerSequence = __make_integer_seq<TIntegerSequence, T, N>;
}
