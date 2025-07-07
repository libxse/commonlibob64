#pragma once

namespace RE
{
	class ACTOR_BASE_DATA
	{
	public:
		enum class Flags : std::int32_t
		{
			Female = 1 << 0,
			Essential = 1 << 1,
			Respawn = 1 << 3,
			AutoCalcStats = 1 << 4,
			PCLevelOffset = 1 << 7,
			NoLowLevelProcessing = 1 << 9,
			NoRumors = 1 << 13,
			Summonable = 1 << 14,
			NoPersuasion = 1 << 15,
			CanCorpseCheck = 1 << 20,
		};

		// members
		REX::EnumSet<Flags> actorBaseFlags;  // 00
		std::uint16_t       spellPoints;     // 04
		std::uint16_t       fatigue;         // 06
		std::uint16_t       barterGold;      // 08
		std::int16_t        level;           // 0A
		std::uint16_t       calcLevelMin;    // 0C
		std::uint16_t       calcLevelMax;    // 0E
	};
	static_assert(sizeof(ACTOR_BASE_DATA) == 0x10);
}
