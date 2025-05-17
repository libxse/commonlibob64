#pragma once

#include "UE/A/AActor.h"
#include "UE/E/EAutoPossessAI.h"
#include "UE/E/EAutoReceiveInput.h"
#include "UE/I/INavAgentInterface.h"
#include "UE/T/TBaseDynamicMulticastDelegate.h"
#include "UE/T/TSparseDynamicDelegate.h"
#include "UE/T/TSubclassOf.h"

namespace UE
{
	class AController;
	class APlayerState;
	class FPawnControllerChangedSignatureInfoGetter;
	class FPawnRestartedSignatureInfoGetter;

	using FPawnControllerChangedSignature_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, APawn*, AController*, AController*>;
	using FPawnControllerChangedSignature = TSparseDynamicDelegate<FPawnControllerChangedSignature_MCSignature, APawn, FPawnControllerChangedSignatureInfoGetter>;
	using FPawnRestartedSignature_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, APawn*>;
	using FPawnRestartedSignature = TSparseDynamicDelegate<FPawnRestartedSignature_MCSignature, APawn, FPawnRestartedSignatureInfoGetter>;

	class APawn :
		public AActor,
		public INavAgentInterface
	{
	public:
		UE_DEFINE_UOBJECT(APawn, AActor, "Engine", "Pawn");

		// override
		virtual ~APawn();

		// members
		std::uint32_t                   useControllerRotationPitch: 1;     // 2A0:0
		std::uint32_t                   useControllerRotationYaw: 1;       // 2A0:1
		std::uint32_t                   useControllerRotationRoll: 1;      // 2A0:2
		std::uint32_t                   canAffectNavigationGeneration: 1;  // 2A0:3
		std::uint32_t                   inputEnabled: 1;                   // 2A0:4
		std::uint32_t                   processingOutsideWorldBounds: 1;   // 2A0:5
		std::uint32_t                   isLocalViewTarget: 1;              // 2A0:6
		float                           baseEyeHeight;                     // 2A4
		TEnumAsByte<EAutoReceiveInput>  autoPossessPlayer;                 // 2A8
		EAutoPossessAI                  autoPossessAI;                     // 2A9
		std::uint8_t                    remoteViewPitch;                   // 2AA
		TSubclassOf<AController>        aiControllerClass;                 // 2B0
		TObjectPtr<APlayerState>        playerState;                       // 2B8
		float                           blendedReplayViewPitch;            // 2C0
		TObjectPtr<AController>         lastHitBy;                         // 2C4
		TObjectPtr<AController>         controller;                        // 2D0
		TObjectPtr<AController>         previousController;                // 2D8
		float                           allowedYawError;                   // 2E0
		FPawnControllerChangedSignature receiveControllerChangedDelegate;  // 2E4
		FPawnRestartedSignature         receiveRestartedDelegate;          // 2E5
		FVector                         controlInputVector;                // 2E8
		FVector                         lastControlInputVector;            // 300
		TSubclassOf<UInputComponent>    overrideInputComponentClass;       // 318
	};
	static_assert(sizeof(APawn) == 0x320);
}
