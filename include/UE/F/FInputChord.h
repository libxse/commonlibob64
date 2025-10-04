#pragma once

#include "UE/F/FKey.h"

namespace UE
{
	class FInputChord
	{
	public:
		FInputChord() = default;

		FInputChord(const FKey a_key) :
			key(a_key)
		{}

	public:
		FKey          key{ EName::None };  // 000
		std::uint32_t shift: 1 { false };  // 018:0
		std::uint32_t ctrl: 1 { false };   // 018:1
		std::uint32_t alt: 1 { false };    // 018:2
		std::uint32_t cmd: 1 { false };    // 018:3
	};
	static_assert(sizeof(FInputChord) == 0x20);
}
