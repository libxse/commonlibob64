#pragma once

namespace UE
{
	class FLinearColor
	{
	public:
		constexpr FLinearColor() = default;

		constexpr FLinearColor(float a_red, float a_green, float a_blue, float a_alpha = 1.0F) :
			r(a_red), g(a_green), b(a_blue), a(a_alpha)
		{}

		// members
		float r{ 0.0F };  // 00
		float g{ 0.0F };  // 04
		float b{ 0.0F };  // 08
		float a{ 1.0F };  // 0C
	};
	static_assert(sizeof(FLinearColor) == 0x10);
}
