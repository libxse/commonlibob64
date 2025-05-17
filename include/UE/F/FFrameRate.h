#pragma once

namespace UE
{
	class FFrameRate
	{
	public:
		// members
		std::int32_t numerator;    // 00
		std::int32_t denominator;  // 04
	};
    static_assert(sizeof(FFrameRate) == 0x8);
}
