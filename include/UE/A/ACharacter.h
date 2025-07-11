#pragma once

#include "UE/A/APawn.h"
#include "UE/E/EMovementMode.h"
#include "UE/F/FBasedMovementInfo.h"
#include "UE/F/FQuat.h"
#include "UE/F/FRepRootMotionMontage.h"
#include "UE/F/FRootMotionMovementParams.h"
#include "UE/F/FRootMotionSourceGroup.h"

namespace UE
{
	class ACharacter;
	class FHitResult;
	class FSimulatedRootMotionReplicatedMove;
	class UCapsuleComponent;
	class UCharacterMovementComponent;
	class USkeletalMeshComponent;

	using FCharacterReachedApexSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void>;
	using FLandedSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, const FHitResult&>;
	using FMovementModeChangedSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, ACharacter*, EMovementMode, std::uint8_t>;
	using FCharacterMovementUpdatedSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, float, FVector, FVector>;

	class ACharacter :
		public APawn
	{
	public:
		UE_DEFINE_UOBJECT(ACharacter, APawn, "Engine", "Character");

		// override
		virtual ~ACharacter();  // 000

		// add
		virtual void    SetBase(UPrimitiveComponent* a_base, const FName a_bone, bool a_notify = true);                                                                 //
		virtual void    CacheInitialMeshOffset(FVector a_relativeLocation, FRotator a_relativeRotation);                                                                //
		virtual void    OnRep_ReplicatedBasedMovement();                                                                                                                //
		virtual void    BaseChange();                                                                                                                                   //
		virtual FQuat   GetBaseRotationOffset();                                                                                                                        //
		virtual FVector GetReplicatedGravityDirection();                                                                                                                //
		virtual void    OnRep_IsCrouched();                                                                                                                             //
		virtual void    ApplyDamageMomentum(float a_damage, const FDamageEvent* a_event, APawn* a_instigator, AActor* a_cause);                                         //
		virtual void    Jump();                                                                                                                                         //
		virtual void    StopJumping();                                                                                                                                  //
		virtual bool    CanJumpInternal_Implementation();                                                                                                               //
		virtual void    ResetJumpState();                                                                                                                               //
		virtual bool    IsJumpProvidingForce();                                                                                                                         //
		virtual float   PlayAnimMontage(UAnimMontage* a_montage, float a_playRate = 1.0F, FName a_startSection = EName::None);                                          //
		virtual void    StopAnimMontage(UAnimMontage* a_montage);                                                                                                       //
		virtual void    LaunchCharacter(FVector a_velocity, bool a_overrideXY, bool a_overrideZ);                                                                       //
		virtual void    OnJumped_Implementation();                                                                                                                      //
		virtual void    Falling();                                                                                                                                      //
		virtual void    NotifyJumpApex();                                                                                                                               //
		virtual void    Landed(const FHitResult& a_hit);                                                                                                                //
		virtual void    OnWalkingOffLedge_Implementation(const FVector& a_impactNormal, const FVector& a_contactNormal, const FVector& a_location, float a_deltaTime);  //
		virtual void    MoveBlockedBy(const FHitResult& a_hit);                                                                                                         //
		virtual void    Crouch(bool a_clientSimulation = false);                                                                                                        //
		virtual void    UnCrouch(bool a_clientSimulation = false);                                                                                                      //
		virtual bool    CanCrouch();                                                                                                                                    //
		virtual void    OnEndCrouch(float a_adjustHalfHeight, float a_adjustScaledHalfHeight);                                                                          //
		virtual void    OnStartCrouch(float a_adjustHalfHeight, float a_adjustScaledHalfHeight);                                                                        //
		virtual void    OnMovementModeChanged(EMovementMode a_mode, std::uint8_t a_previous);                                                                           //
		virtual bool    ShouldNotifyLanded(const FHitResult& a_hit);                                                                                                    //
		virtual void    CheckJumpInput(float a_deltaTime);                                                                                                              //
		virtual void    ClearJumpInput(float a_deltaTime);                                                                                                              //
		virtual float   GetJumpMaxHoldTime();                                                                                                                           //
		virtual void    ClientCheatWalk_Implementation();                                                                                                               //
		virtual void    ClientCheatFly_Implementation();                                                                                                                //
		virtual void    ClientCheatGhost_Implementation();                                                                                                              //
		virtual void    RootMotionDebugClientPrintOnScreen_Implementation(const FString* a_string);                                                                     //
		virtual void    OnUpdateSimulatedPosition(const FVector& a_location, const FQuat& a_rotation);                                                                  //

		// members
		TObjectPtr<USkeletalMeshComponent>         mesh;                                          // 320
		TObjectPtr<UCharacterMovementComponent>    characterMovement;                             // 328
		TObjectPtr<UCapsuleComponent>              capsuleComponent;                              // 330
		FBasedMovementInfo                         basedMovement;                                 // 338
		FBasedMovementInfo                         replicatedBasedMovement;                       // 388
		float                                      animRootMotionTranslationScale;                // 3D8
		FVector                                    baseTranslationOffset;                         // 3E0
		FQuat                                      baseRotationOffset;                            // 400
		float                                      replicatedServerLastTransformUpdateTimeStamp;  // 420
		float                                      replayLastTransformUpdateTimeStamp;            // 424
		std::uint8_t                               replicatedMovementMode;                        // 428
		FVector_NetQuantizeNormal                  replicatedGravityDirection;                    // 430
		bool                                       inBaseReplication;                             // 448
		FVector_NetQuantizeNormal                  preNetReceivedGravityDirection;                // 450
		float                                      crouchedEyeHeight;                             // 468
		std::uint32_t                              isCrouched: 1;                                 // 46C:0
		std::uint32_t                              proxyIsJumpForceApplied: 1;                    // 46C:1
		std::uint32_t                              pressedJump: 1;                                // 46C:2
		std::uint32_t                              clientUpdating: 1;                             // 46C:3
		std::uint32_t                              clientWasFalling: 1;                           // 46C:4
		std::uint32_t                              clientResimulateRootMotion: 1;                 // 46C:5
		std::uint32_t                              clientResimulateRootMotionSources: 1;          // 46C:6
		std::uint32_t                              simGravityDisabled: 1;                         // 46C:7
		std::uint32_t                              clientCheckEncroachmentOnNetUpdate: 1;         // 46D:0
		std::uint32_t                              serverMoveIgnoreRootMotion: 1;                 // 46D:1
		std::uint32_t                              wasJumping: 1;                                 // 46D:2
		float                                      jumpKeyHoldTime;                               // 470
		float                                      jumpForceTimeRemaining;                        // 474
		float                                      proxyJumpForceStartedTime;                     // 478
		float                                      jumpMaxHoldTime;                               // 47C
		std::int32_t                               jumpMaxCount;                                  // 480
		std::int32_t                               jumpCurrentCount;                              // 484
		std::int32_t                               jumpCurrentCountPreJump;                       // 488
		std::uint32_t                              numActorOverlapEventsCounter;                  // 48C
		FCharacterReachedApexSignature             onReachedJumpApex;                             // 490
		FLandedSignature                           landedDelegate;                                // 4A0
		FMovementModeChangedSignature              movementModeChangedDelegate;                   // 4B0
		FCharacterMovementUpdatedSignature         onCharacterMovementUpdated;                    // 4C0
		FRootMotionSourceGroup                     savedRootMotion;                               // 4D0
		FRootMotionMovementParams                  clientRootMotionParams;                        // 520
		TArray<FSimulatedRootMotionReplicatedMove> rootMotionRepMoves;                            // 590
		FRepRootMotionMontage                      repRootMotion;                                 // 5A0
	};
	static_assert(sizeof(ACharacter) == 0x680);
}
