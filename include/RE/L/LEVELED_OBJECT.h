#pragma once

namespace RE
{
	class TESForm;

	class LEVELED_OBJECT
	{
	public:
		// members
		std::uint16_t level;  // 000
		TESForm*      form;   // 008
		std::uint16_t count;  // 010
	};
	static_assert(sizeof(LEVELED_OBJECT) == 0x18);
}
