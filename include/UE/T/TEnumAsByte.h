#pragma once

namespace UE
{
	template <class T>
	class TEnumAsByte
	{
	public:
		constexpr TEnumAsByte() = default;

		constexpr TEnumAsByte(T a_value) :
			value(static_cast<std::uint8_t>(a_value))
		{}

		constexpr bool operator==(T a_value) const
		{
			return static_cast<T>(value) == a_value;
		}

		constexpr bool operator==(TEnumAsByte a_value) const
		{
			return value == a_value.value;
		}

		constexpr operator T() const
		{
			return static_cast<T>(value);
		}

		// members
		std::uint8_t value;  // 000
	};
}
