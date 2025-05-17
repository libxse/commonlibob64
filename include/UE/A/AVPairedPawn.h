#pragma once

#include "UE/A/ACharacter.h"
#include "UE/E/EOblivionAnimGroup.h"
#include "UE/E/EVActorValues.h"
#include "UE/F/FPoseSnapshot.h"
#include "UE/I/IReactToFreezeInterface.h"
#include "UE/I/IVAudioPlayable.h"
#include "UE/I/IVPhysicsControllable.h"
#include "UE/I/IVTransformPairable.h"
#include "UE/T/TBaseDynamicDelegate.h"

namespace UE
{
	class UAnimSequence;
	class UAnimSequenceBase;
	class UBoxComponent;
	class UCurveFloat;
	class UPhysicalAnimationComponent;
	class USoundBase;
	class UStaticMeshComponent;
	class UVActiveEffectsPairingComponent;
	class UVActorValuesPairingComponent;
	class UVAltarAkComponent;
	class UVAnimationPairingComponent;
	class UVCharacterFadeInOutComponent;
	class UVCharacterStatePairingComponent;
	class UVMergedSkeletalMeshComponent;
	class UVPairedPawnMovementComponent;
	class UVPairedPawnStateMachineComponent;
	class UVPawnSoundPairingComponent;
	class UVPhysicsControllerComponent;
	class UVTESObjectRefComponent;
	class UVTransformPairingComponent;
	class UVWeaponsPairingComponent;
	class UWidgetComponent;

	using FOnActorValueChanged = TBaseDynamicDelegate<FNotThreadSafeDelegateMode, void, EVActorValues, float, float, float, float>;
	using FOnEnterLowFatigueState = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void>;
	using FOnExitLowFatigueState = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void>;
	using FOnRequestLinkDynamicAnimLayers = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void>;

	class AVPairedPawn :
		public ACharacter,
		public IReactToFreezeInterface,
		public IVPhysicsControllable,
		public IVTransformPairable,
		public IVAudioPlayable
	{
	public:
		UE_DEFINE_UOBJECT(AVPairedPawn, ACharacter, "Altar", "VPairedPawn");

		// override
		virtual ~AVPairedPawn();  // 00

		// members
		float                                         turnInPlaceAngleThreshold;                       // 6C8
		float                                         actorForwardPoseOffset;                          // 6CC
		FVector                                       lookAtPoint;                                     // 6D0
		bool                                          shouldUseLookAtPoint;                            // 6E8
		bool                                          inEntityDebugMode;                               // 6E9
		FOnEnterLowFatigueState                       onEnterLowFatigueState;                          // 6F0
		FOnExitLowFatigueState                        onExitLowFatigueState;                           // 700
		FOnActorValueChanged                          actorValueChangedDelegate_Paralysis;             // 710
		TObjectPtr<USceneComponent>                   fakeRoot;                                        // 720
		TArray<TObjectPtr<UPrimitiveComponent>>       secondaryColliders;                              // 728
		TObjectPtr<UCapsuleComponent>                 physicsBodyCollider;                             // 738
		TObjectPtr<UBoxComponent>                     worldLimitDetectionBox;                          // 740
		TObjectPtr<USkeletalMeshComponent>            mainSkeletalMeshComponent;                       // 748
		TObjectPtr<UStaticMeshComponent>              drawnArrowMeshComponent;                         // 750
		TObjectPtr<UVPairedPawnStateMachineComponent> stateMachineComponent;                           // 758
		TObjectPtr<UVMergedSkeletalMeshComponent>     mergedMeshComponent;                             // 760
		TObjectPtr<UActorComponent>                   statusEffectComponent;                           // 768
		TObjectPtr<UVPairedPawnMovementComponent>     pairedPawnMovementComponent;                     // 770
		TObjectPtr<UWidgetComponent>                  pawnDebugInfoWidgetComponent;                    // 778
		TObjectPtr<UWidgetComponent>                  entityDetailsDebugWidgetComponent;               // 780
		TObjectPtr<UVPhysicsControllerComponent>      physicsControllerComponent;                      // 788
		TObjectPtr<UVAltarAkComponent>                akAudioComponent;                                // 790
		TObjectPtr<UPhysicalAnimationComponent>       physicalAnimationComponent;                      // 798
		TObjectPtr<UVCharacterFadeInOutComponent>     characterFadeInOutComponent;                     // 7A0
		FOnRequestLinkDynamicAnimLayers               onRequestLinkDynamicAnimLayers;                  // 7A8
		TObjectPtr<UVTESObjectRefComponent>           tesRefComponent;                                 // 7B8
		TObjectPtr<UVTransformPairingComponent>       transformPairingComponent;                       // 7C0
		TObjectPtr<UVAnimationPairingComponent>       animationPairingComponent;                       // 7C8
		TObjectPtr<UVPawnSoundPairingComponent>       pawnSoundPairingComponent;                       // 7D0
		TObjectPtr<UVWeaponsPairingComponent>         weaponsPairingComponent;                         // 7D8
		TObjectPtr<UVCharacterStatePairingComponent>  oblivionActorStatePairingComponent;              // 7E0
		TObjectPtr<UVActorValuesPairingComponent>     actorValuesPairingComponent;                     // 7E8
		TObjectPtr<UVActiveEffectsPairingComponent>   activeEffectsPairingComponent;                   // 7F0
		float                                         lightingUpdateFrequency;                         // 7F8
		float                                         currentLightingValue;                            // 7FC
		float                                         currentLightingValueWithTorch;                   // 800
		bool                                          doesDetectionLightingAllowShadowOcclusionTests;  // 804
		TObjectPtr<USoundBase>                        hitSoundCue;                                     // 808
		bool                                          inCombatStance;                                  // 810
		bool                                          isImmuneToShieldBashEffect;                      // 811
		TSet<AActor*>                                 allowedMeleeTargets;                             // 818
		bool                                          restrictedMeleeTargeting;                        // 868
		float                                         yawRotationDelta;                                // 86C
		UAnimSequenceBase*                            specialAnimSequence;                             // 870
		UAnimSequence*                                dynamicAnimSequence;                             // 878
		FPoseSnapshot                                 lastPoseSnapshot;                                // 880
		bool                                          isRagdollFacingUp;                               // 8B8
		EOblivionAnimGroup                            currentSpellCastAnimGroup;                       // 8B9
		bool                                          isLanding;                                       // 8BA
		bool                                          useRotationSpeedCurve;                           // 8BB
		TObjectPtr<UCurveFloat>                       rotationSpeedCurve;                              // 8C0
																									   // ...
	};
	//static_assert(sizeof(AVPairedPawn) == 0xE30);
}
