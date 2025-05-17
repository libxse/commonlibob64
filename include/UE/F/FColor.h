#pragma once

namespace UE
{
	class FColor
	{
	public:
		constexpr FColor() = default;

		explicit constexpr FColor(std::uint32_t a_value)
		{
			*this = std::bit_cast<FColor>(a_value);
		}

		constexpr FColor(std::uint8_t a_red, std::uint8_t a_green, std::uint8_t a_blue, std::uint8_t a_alpha = 255u) :
			r(a_red), g(a_green), b(a_blue), a(a_alpha)
		{}

		// members
		std::uint8_t r{ 0 };    // 00
		std::uint8_t g{ 0 };    // 01
		std::uint8_t b{ 0 };    // 02
		std::uint8_t a{ 255 };  // 03
	};
	static_assert(sizeof(FColor) == 0x4);
}
