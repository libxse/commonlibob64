#pragma once

namespace UE::Math
{
	template <class T>
	class TIntPoint
	{
	public:
		constexpr TIntPoint(T a_x, T a_y) :
			x(a_x), y(a_y)
		{}

		// members
		T x;
		T y;
	};
	static_assert(sizeof(TIntPoint<std::int32_t>) == 0x8);
	static_assert(sizeof(TIntPoint<std::int64_t>) == 0x10);
}
