#pragma once

namespace UE
{
	struct FMath
	{
		template <class T>
		static constexpr T __forceinline DivideAndRoundUp(T a_x, T a_y)
		{
			return (a_x + a_y - 1) / a_y;
		}
	};
}
