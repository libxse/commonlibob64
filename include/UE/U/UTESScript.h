#pragma once

#include "UE/E/EScriptType.h"
#include "UE/T/TEnumAsByte.h"
#include "UE/U/UTESForm.h"

namespace UE
{
	class UTESScript :
		public UTESForm
	{
	public:
		UE_DEFINE_UOBJECT(UTESScript, UTESForm, "Altar", "TESScript");

		// override
		virtual ~UTESScript();  // 00

		// members
		FString                  source;  // 0D8
		TEnumAsByte<EScriptType> type;    // 0E8
	};
	static_assert(sizeof(UTESScript) == 0x0F0);
}
