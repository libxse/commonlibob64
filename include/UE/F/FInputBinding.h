#pragma once

namespace UE
{
	class FInputBinding
	{
	public:
		FInputBinding() = default;

		// members
		std::uint8_t consumeInput: 1 { true };        // 000:0
		std::uint8_t executeWhenPaused: 1 { false };  // 000:1
	};
	static_assert(sizeof(FInputBinding) == 0x1);
}
