#pragma once

#include "UE/E/EVBossCategory.h"
#include "UE/U/UActorComponent.h"

namespace UE
{
	class UTESForm;
	class VPairingEntry;

	using FVPairingInitializationDelegate = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void>;
	using FVUnpairedDelegate = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void>;

	class UVTESObjectRefComponent :
		public UActorComponent
	{
	public:
		UE_DEFINE_UOBJECT(UVTESObjectRefComponent, UActorComponent, "Altar", "VTESObjectRefComponent");

		// override
		virtual ~UVTESObjectRefComponent();  // 00

		// members
		std::uint32_t                   formIDInstance;          // 0A0
		FGuid                           guid;                    // 0A4
		FString                         cellName;                // 0B8
		FString                         cellNameAtRuntime;       // 0C8
		UTESForm*                       tesForm;                 // 0D8
		bool                            isPaired;                // 0E0
		FVPairingInitializationDelegate onInitializedAndPaired;  // 0E8
		FVUnpairedDelegate              onUnpaired;              // 0F8
		VPairingEntry*                  ownerPairingEntry;       // 108
		EVBossCategory                  bossTag;                 // 110
	};
	static_assert(sizeof(UVTESObjectRefComponent) == 0x118);
}
