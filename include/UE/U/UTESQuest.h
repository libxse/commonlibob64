#pragma once

#include "UE/U/UTESForm.h"

namespace UE
{
	class UTESQuest :
		public UTESForm
	{
	public:
		UE_DEFINE_UOBJECT(UTESQuest, UTESForm, "Altar", "TESQuest");

		// override
		virtual ~UTESQuest();  // 00
	};
	static_assert(sizeof(UTESQuest) == 0x0D8);
}
