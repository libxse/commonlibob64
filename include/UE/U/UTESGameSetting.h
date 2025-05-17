#pragma once

#include "UE/U/UTESForm.h"

namespace UE
{
	class UTESGameSetting :
		public UTESForm
	{
	public:
		UE_DEFINE_UOBJECT(UTESGameSetting, UTESForm, "Altar", "TESGameSetting");

		// override
		virtual ~UTESGameSetting();  // 00

		// members
		std::int32_t intValue;     // 0D8
		float        floatValue;   // 0DC
		FString      stringValue;  // 0E0
	};
	static_assert(sizeof(UTESGameSetting) == 0x0F0);
}
