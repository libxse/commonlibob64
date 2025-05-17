#pragma once

#include "UE/U/UCheatManager.h"

namespace UE
{
	class UUserWidget;

	class UAltarCheatManager :
		public UCheatManager
	{
	public:
		UE_DEFINE_UOBJECT(UAltarCheatManager, UCheatManager, "Altar", "AltarCheatManager");

		// override
		virtual ~UAltarCheatManager();  // 00

		// members
		TWeakObjectPtr<AActor>   selectedActor;               // 088
		TSubclassOf<UUserWidget> graphicsDebugWidget;         // 090
		bool                     isGraphicsDebugWidgetShown;  // 098
		bool                     allowSetStage;               // 09C
	};
	static_assert(sizeof(UAltarCheatManager) == 0xA0);
}
