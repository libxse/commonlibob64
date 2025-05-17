#pragma once

#include "UE/U/UTESForm.h"

namespace UE
{
	class FTESResponse;

	class UTESTopicInfo :
		public UTESForm
	{
	public:
		UE_DEFINE_UOBJECT(UTESTopicInfo, UTESForm, "Altar", "TESTopicInfo");

		// override
		virtual ~UTESTopicInfo();  // 00

		// members
		TArray<FTESResponse> responses;  // 0D8
	};
	static_assert(sizeof(UTESTopicInfo) == 0x0E8);
}
