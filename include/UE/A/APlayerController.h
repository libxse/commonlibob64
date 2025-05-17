#pragma once

#include "UE/A/AController.h"
#include "UE/I/IWorldPartitionStreamingSourceProvider.h"
#include "UE/T/TSubclassOf.h"

namespace UE
{
	class AHUD;
	class APlayerCameraManager;
	class UCheatManager;
	class UPlayer;
	class UPrimitiveComponent;

	class APlayerController :
		public AController,
		public IWorldPartitionStreamingSourceProvider
	{
	public:
		UE_DEFINE_UOBJECT(APlayerController, AController, "Engine", "PlayerController");

		// override
		virtual ~APlayerController();

		// members
		TObjectPtr<UPlayer>                         player;                              // 338
		TObjectPtr<APawn>                           acknowledgedPawn;                    // 340
		TObjectPtr<AHUD>                            myHUD;                               // 348
		TObjectPtr<APlayerCameraManager>            playerCameraManager;                 // 350
		TSubclassOf<APlayerCameraManager>           playerCameraManagerClass;            // 358
		bool                                        autoManageActiveCameraTarget;        // 360
		FRotator                                    targetViewRotation;                  // 368
		FRotator                                    blendedTargetViewRotation;           // 380
		float                                       smoothTargetViewRotationSpeed;       // 398
		float                                       localPlayerCachedLODDistanceFactor;  // 39C
		TArray<TObjectPtr<AActor>>                  hiddenActors;                        // 3A0
		TArray<TWeakObjectPtr<UPrimitiveComponent>> hiddenPrimitiveComponents;           // 3B0
		bool                                        renderPrimitiveComponents;           // 3C0
		float                                       lastSpectatorStateSynchTime;         // 3C4
		FVector                                     lastSpectatorSyncLocation;           // 3C8
		FRotator                                    lastSpectatorSyncRotation;           // 3E0
		std::int32_t                                clientCap;                           // 3F8
		TObjectPtr<UCheatManager>                   cheatManager;                        // 400
																						 // ...
	};
	//static_assert(sizeof(APlayerController) == 0x858);
}
