#pragma once

#include "UE/U/UTESForm.h"

namespace UE
{
	class UATMEventPreset;

	class UTESWeather :
		public UTESForm
	{
	public:
		UE_DEFINE_UOBJECT(UTESWeather, UTESForm, "Altar", "TESWeather");

		// override
		virtual ~UTESWeather();

		// members
		UATMEventPreset* preset;  // 0D8
	};
	static_assert(sizeof(UTESWeather) == 0xE0);
}
