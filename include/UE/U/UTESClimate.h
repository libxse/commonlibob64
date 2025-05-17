#pragma once

#include "UE/F/FTESWeatherList.h"
#include "UE/U/UTESForm.h"

namespace UE
{
	class UATMPreset;

	class UTESClimate :
		public UTESForm
	{
	public:
		UE_DEFINE_UOBJECT(UTESClimate, UTESForm, "Altar", "TESClimate");

		// override
		virtual ~UTESClimate();  // 00

		// members
		float           hourlyIncrements;  // 0D8
		FTESWeatherList weatherList;       // 0E0
		UATMPreset*     preset;            // 0F0
		float           sunriseBegin;      // 0F8
		float           sunriseEnd;        // 0FC
		float           sunsetBegin;       // 100
		float           sunsetEnd;         // 104
		std::uint8_t    volatility;        // 108
		std::uint8_t    moonPhasesDays;    // 109
		bool            useMasser;         // 10A
		bool            useSecunda;        // 10B
	};
	static_assert(sizeof(UTESClimate) == 0x110);
}
