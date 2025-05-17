#pragma once

namespace UE::Math
{
	template <class T>
	class TVector2
	{
	public:
		constexpr TVector2(T a_x, T a_y) :
			x(a_x), y(a_y)
		{}

		// members
		T x;
		T y;
	};
	static_assert(sizeof(TVector2<float>) == 0x8);
	static_assert(sizeof(TVector2<double>) == 0x10);
}
