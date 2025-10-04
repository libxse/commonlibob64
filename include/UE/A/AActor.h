#pragma once

#include "UE/E/EActorUpdateOverlapsMethod.h"
#include "UE/E/EAutoReceiveInput.h"
#include "UE/E/ECollisionResponse.h"
#include "UE/E/EEndPlayReason.h"
#include "UE/E/ELifetimeCondition.h"
#include "UE/E/ENetDormancy.h"
#include "UE/E/ENetRole.h"
#include "UE/E/EPhysicsReplicationMode.h"
#include "UE/E/ESpawnActorCollisionHandlingMethod.h"
#include "UE/E/ETouchIndex.h"
#include "UE/F/FActorTickFunction.h"
#include "UE/F/FBox.h"
#include "UE/F/FKey.h"
#include "UE/F/FRenderCommandFence.h"
#include "UE/F/FRepAttachment.h"
#include "UE/F/FRepMovement.h"
#include "UE/F/FTimerHandle.h"
#include "UE/F/FTransform.h"
#include "UE/T/TObjectPtr.h"
#include "UE/T/TSubclassOf.h"
#include "UE/T/TWeakObjectPtr.h"
#include "UE/U/UObject.h"

namespace UE::Net
{
	class FReplicatedComponentInfo;
}

namespace UE
{
	class AController;
	class APawn;
	class APhysicsVolume;
	class APlayerController;
	class FCollisionImpactData;
	class FDamageEvent;
	class FDebugDisplayInfo;
	class FHitResult;
	class FInBunch;
	class FMinimalViewInfo;
	class FNetViewer;
	class FOutBunch;
	class FPointDamageEvent;
	class FRadialDamageEvent;
	class FReplicationFlags;
	class FRigidBodyCollisionInfo;
	class IRepChangedPropertyTracker;
	class UActorChannel;
	class UActorComponent;
	class UCanvas;
	class UChildActorComponent;
	class UDamageType;
	class UInputComponent;
	class UInterface;
	class UNetConnection;
	class UPlayer;
	class UPrimitiveComponent;
	class USceneComponent;

	enum class ECollisionChannel : std::int32_t;

	class AActor :
		public UObject
	{
	public:
		UE_DEFINE_UOBJECT(AActor, UObject, "Engine", "Actor");

		enum class EActorBeginPlayState : std::uint8_t
		{
			HasNotBegunPlay,
			BeginningPlay,
			HasBegunPlay,
		};

		// override
		virtual ~AActor();  // 000

		// add
		virtual bool                     DoesDisablePhysicsAfterOOB();                                                                                                                                                                                                     // 057
		virtual void                     OnRep_ReplicateMovement();                                                                                                                                                                                                        // 058
		virtual void                     TearOff();                                                                                                                                                                                                                        // 059
		virtual bool                     HasNetOwner();                                                                                                                                                                                                                    // 05A
		virtual bool                     HasLocalNetOwner();                                                                                                                                                                                                               // 05B
		virtual void                     OnRep_Owner();                                                                                                                                                                                                                    // 05C
		virtual void                     SetReplicateMovement(bool a_replicate);                                                                                                                                                                                           // 05D
		virtual void                     OnRep_AttachmentReplication();                                                                                                                                                                                                    // 05E
		virtual bool                     IsReplicationPausedForConnection(const FNetViewer& a_viewer);                                                                                                                                                                     // 05F
		virtual void                     OnReplicationPausedChanged(bool a_paused);                                                                                                                                                                                        // 060
		virtual bool                     ReplicateSubobjects(UActorChannel* a_channel, FOutBunch* a_bunch, FReplicationFlags* a_flags);                                                                                                                                    // 061
		virtual void                     OnSubobjectCreatedFromReplication(UObject* a_object);                                                                                                                                                                             // 062
		virtual void                     OnSubobjectDestroyFromReplication(UObject* a_object);                                                                                                                                                                             // 063
		virtual void                     PreReplication(IRepChangedPropertyTracker& a_tracker);                                                                                                                                                                            // 064
		virtual void                     PreReplicationForReplay(IRepChangedPropertyTracker& a_tracker);                                                                                                                                                                   // 065
		virtual void                     RewindForReplay();                                                                                                                                                                                                                // 066
		virtual void                     OnRep_Instigator();                                                                                                                                                                                                               // 067
		virtual void                     EnableInput(APlayerController* a_controller);                                                                                                                                                                                     // 068
		virtual void                     CreateInputComponent(TSubclassOf<UInputComponent> a_component);                                                                                                                                                                   // 069
		virtual void                     DisableInput(APlayerController* a_controller);                                                                                                                                                                                    // 06A
		virtual void                     GetActorBounds(bool a_onlyColliding, FVector& a_origin, FVector& a_boxExtent, bool a_includeChildren);                                                                                                                            // 06B
		virtual FVector                  GetVelocity();                                                                                                                                                                                                                    // 06C
		virtual void                     SetActorHiddenInGame(bool a_hidden);                                                                                                                                                                                              // 06D
		virtual void                     K2_DestroyActor();                                                                                                                                                                                                                // 06E
		virtual void                     AddTickPrerequisiteActor(AActor* a_actor);                                                                                                                                                                                        // 06F
		virtual void                     AddTickPrerequisiteComponent(UActorComponent* a_component);                                                                                                                                                                       // 070
		virtual void                     RemoveTickPrerequisiteActor(AActor* a_actor);                                                                                                                                                                                     // 071
		virtual void                     RemoveTickPrerequisiteComponent(UActorComponent* a_component);                                                                                                                                                                    // 072
		virtual void                     BeginPlay();                                                                                                                                                                                                                      // 073
		virtual void                     EndPlay(const EEndPlayReason a_reason);                                                                                                                                                                                           // 074
		virtual void                     NotifyActorBeginOverlap(AActor*);                                                                                                                                                                                                 // 075
		virtual void                     NotifyActorEndOverlap(AActor*);                                                                                                                                                                                                   // 076
		virtual void                     NotifyActorBeginCursorOver();                                                                                                                                                                                                     // 077
		virtual void                     NotifyActorEndCursorOver();                                                                                                                                                                                                       // 078
		virtual void                     NotifyActorOnClicked(FKey a_key);                                                                                                                                                                                                 // 079
		virtual void                     NotifyActorOnReleased(FKey a_key);                                                                                                                                                                                                // 07A
		virtual void                     NotifyActorOnInputTouchBegin(const ETouchIndex a_index);                                                                                                                                                                          // 07B
		virtual void                     NotifyActorOnInputTouchEnd(const ETouchIndex a_index);                                                                                                                                                                            // 07C
		virtual void                     NotifyActorOnInputTouchEnter(const ETouchIndex a_index);                                                                                                                                                                          // 07D
		virtual void                     NotifyActorOnInputTouchLeave(const ETouchIndex a_index);                                                                                                                                                                          // 07E
		virtual void                     NotifyHit(UPrimitiveComponent* a_selfComponent, AActor* a_otherActor, UPrimitiveComponent* a_otherComponent, bool a_selfMoved, FVector a_hitLocation, FVector a_hitNormal, FVector a_hitNormalImpulse, const FHitResult& a_hit);  // 07F
		virtual void                     SetLifeSpan(float a_lifespan);                                                                                                                                                                                                    // 080
		virtual float                    GetLifeSpan();                                                                                                                                                                                                                    // 081
		virtual bool                     IsRuntimeOnly();                                                                                                                                                                                                                  // 082
		virtual void                     GatherCurrentMovement();                                                                                                                                                                                                          // 083
		virtual USceneComponent*         GetDefaultAttachComponent();                                                                                                                                                                                                      // 084
		virtual void                     ApplyWorldOffset(const FVector& a_offset, bool a_worldShift);                                                                                                                                                                     // 085
		virtual bool                     IsLevelBoundsRelevant();                                                                                                                                                                                                          // 086
		virtual bool                     IsHLODRelevant();                                                                                                                                                                                                                 // 087
		virtual bool                     HasHLODRelevantComponents();                                                                                                                                                                                                      // 088
		virtual TArray<UActorComponent*> GetHLODRelevantComponents();                                                                                                                                                                                                      // 089
		virtual float                    GetNetPriority(const FVector& a_viewPos, const FVector& a_viewDir, AActor* a_viewer, AActor* a_target, UActorChannel* a_channel, float a_time, bool a_lowBandwidth);                                                              // 08A
		virtual float                    GetReplayPriority(const FVector& a_viewPos, const FVector& a_viewDir, AActor* a_viewer, AActor* a_target, UActorChannel* a_channel, float a_time);                                                                                // 08B
		virtual bool                     GetNetDormancy(const FVector& a_viewPos, const FVector& a_viewDir, AActor* a_viewer, AActor* a_target, UActorChannel* a_channel, float a_time, bool a_lowBandwidth);                                                              // 08C
		virtual void                     OnActorChannelOpen(FInBunch& a_bunch, UNetConnection* a_connection);                                                                                                                                                              // 08D
		virtual bool                     UseShortConnectTimeout();                                                                                                                                                                                                         // 08E
		virtual void                     OnSerializeNewActor(FOutBunch& a_bunch);                                                                                                                                                                                          // 08F
		virtual void                     OnNetCleanup(UNetConnection* a_connection);                                                                                                                                                                                       // 090
		virtual void                     SetActorTickEnabled(bool a_enabled);                                                                                                                                                                                              // 091
		virtual void                     TickActor(float a_deltaTime, ELevelTick a_type, FActorTickFunction& a_func);                                                                                                                                                      // 092
		virtual void                     AsyncPhysicsTickActor(float a_deltaTime, float a_simTime);                                                                                                                                                                        // 093
		virtual void                     PostActorCreated();                                                                                                                                                                                                               // 094
		virtual void                     LifeSpanExpired();                                                                                                                                                                                                                // 095
		virtual void                     PostNetReceiveRole();                                                                                                                                                                                                             // 096
		virtual void                     PostNetInit();                                                                                                                                                                                                                    // 097
		virtual void                     OnRep_ReplicatedMovement();                                                                                                                                                                                                       // 098
		virtual void                     PostNetReceiveLocationAndRotation();                                                                                                                                                                                              // 099
		virtual void                     PostNetReceiveVelocity(const FVector& a_velocity);                                                                                                                                                                                // 09A
		virtual void                     PostNetReceivePhysicState();                                                                                                                                                                                                      // 09B
		virtual void                     SetOwner(AActor* a_owner);                                                                                                                                                                                                        // 09C
		virtual bool                     CheckStillInWorld();                                                                                                                                                                                                              // 09D
		virtual APhysicsVolume*          GetPhysicsVolume();                                                                                                                                                                                                               // 09E
		virtual void                     Tick(float a_deltaTime);                                                                                                                                                                                                          // 09F
		virtual bool                     ShouldTickIfViewportsOnly();                                                                                                                                                                                                      // 0A0
		virtual bool                     IsNetRelevantFor(const AActor* a_viewer, const AActor* a_target, const FVector& a_location);                                                                                                                                      // 0A1
		virtual bool                     IsReplayRelevantFor(const AActor* a_viewer, const AActor* a_target, const FVector& a_location, const float a_cullDistanceSquared);                                                                                                // 0A2
		virtual bool                     IsRelevancyOwnerFor(const AActor* a_actor, const AActor* a_actorOwner, const AActor* a_actorConnection);                                                                                                                          // 0A3
		virtual void                     PreInitializeComponents();                                                                                                                                                                                                        // 0A4
		virtual void                     PostInitializeComponents();                                                                                                                                                                                                       // 0A5
		virtual void                     DispatchPhysicsCollisionHit(const FRigidBodyCollisionInfo& a_info, const FRigidBodyCollisionInfo& a_infoExtra, const FCollisionImpactData& a_data);                                                                               // 0A6
		virtual const AActor*            GetNetOwner();                                                                                                                                                                                                                    // 0A7
		virtual UPlayer*                 GetNetOwningPlayer();                                                                                                                                                                                                             // 0A8
		virtual UNetConnection*          GetNetConnection();                                                                                                                                                                                                               // 0A9
		virtual bool                     DestroyNetworkActorHandled();                                                                                                                                                                                                     // 0AA
		virtual bool                     IsSelectionParentOfAttachedActors();                                                                                                                                                                                              // 0AB
		virtual bool                     IsSelectionChild();                                                                                                                                                                                                               // 0AC
		virtual AActor*                  GetSelectionParent();                                                                                                                                                                                                             // 0AD
		virtual AActor*                  GetRootSelectionParent();                                                                                                                                                                                                         // 0AE
		virtual void                     PushSelectionToProxies();                                                                                                                                                                                                         // 0AF
		virtual void                     RegisterAllComponents();                                                                                                                                                                                                          // 0B0
		virtual void                     PreRegisterAllComponents();                                                                                                                                                                                                       // 0B1
		virtual void                     PostRegisterAllComponents();                                                                                                                                                                                                      // 0B2
		virtual void                     UnregisterAllComponents(bool a_reregister = false);                                                                                                                                                                               // 0B3
		virtual void                     PostUnregisterAllComponents();                                                                                                                                                                                                    // 0B4
		virtual void                     ReregisterAllComponents();                                                                                                                                                                                                        // 0B5
		virtual void                     MarkComponentsAsPendingKill();                                                                                                                                                                                                    // 0B6
		virtual void                     MarkComponentsAsGarbage(bool);                                                                                                                                                                                                    // 0B7
		virtual void                     InvalidateLightingCacheDetailed(bool a_translationOnly);                                                                                                                                                                          // 0B8
		virtual bool                     TeleportTo(const FVector& a_location, const FRotator& a_rotation, bool a_test, bool a_noCheck);                                                                                                                                   // 0B9
		virtual void                     TeleportSucceeded(bool a_test);                                                                                                                                                                                                   // 0BA
		virtual void                     ClearCrossLevelReferences();                                                                                                                                                                                                      // 0BB
		virtual bool                     IsBasedOnActor(const AActor* a_actor);                                                                                                                                                                                            // 0BC
		virtual bool                     IsAttachedTo(const AActor* a_actor);                                                                                                                                                                                              // 0BD
		virtual void                     OnConstruction(const FTransform& a_transform);                                                                                                                                                                                    // 0BE
		virtual void                     BeginReplication();                                                                                                                                                                                                               // 0BF
		virtual void                     EndReplication(const EEndPlayReason a_reason);                                                                                                                                                                                    // 0C0
		virtual void                     RegisterActorTickFunctions(bool a_register);                                                                                                                                                                                      // 0C1
		virtual void                     Destroyed();                                                                                                                                                                                                                      // 0C2
		virtual void                     FellOutOfWorld(const UDamageType& a_damageType);                                                                                                                                                                                  // 0C3
		virtual void                     OutsideWorldBounds();                                                                                                                                                                                                             // 0C4
		virtual FBox                     GetComponentsBoundingBox(bool a_nonColliding, bool a_children);                                                                                                                                                                   // 0C5
		virtual FBox                     CalculateComponentsBoundingBoxInLocalSpace(bool a_nonColliding, bool a_children);                                                                                                                                                 // 0C6
		virtual void                     GetComponentsBoundingCylinder(float& a_collisionRadius, float& a_collisionHalfHeight, bool a_nonColliding, bool a_children);                                                                                                      // 0C7
		virtual void                     GetSimpleCollisionCylinder(float& a_collisionRadius, float& a_collisionHalfHeight);                                                                                                                                               // 0C8
		virtual bool                     IsRootComponentCollisionRegistered();                                                                                                                                                                                             // 0C9
		virtual void                     TornOff();                                                                                                                                                                                                                        // 0CA
		virtual ECollisionResponse       GetComponentsCollisionResponseToChannel(ECollisionChannel a_channel);                                                                                                                                                             // 0CB
		virtual bool                     CanBeBaseForCharacter(APawn* a_pawn);                                                                                                                                                                                             // 0CC
		virtual float                    TakeDamage(float a_damage, const FDamageEvent& a_event, AController* a_eventInstigator, AActor* a_cause);                                                                                                                         // 0CD
		virtual float                    InternalTakeRadialDamage(float a_damage, const FRadialDamageEvent& a_event, AController* a_eventInstigator, AActor* a_cause);                                                                                                     // 0CE
		virtual float                    InternalTakePointDamage(float a_damage, const FPointDamageEvent& a_event, AController* a_eventInstigator, AActor* a_cause);                                                                                                       // 0CF
		virtual void                     BecomeViewTarget(APlayerController* a_player);                                                                                                                                                                                    // 0D0
		virtual void                     EndViewTarget(APlayerController* a_player);                                                                                                                                                                                       // 0D1
		virtual void                     CalcCamera(float a_deltaTime, FMinimalViewInfo& a_result);                                                                                                                                                                        // 0D2
		virtual bool                     HasActiveCameraComponent();                                                                                                                                                                                                       // 0D3
		virtual bool                     HasActivePawnControlCameraComponent();                                                                                                                                                                                            // 0D4
		virtual FString                  GetHumanReadableName();                                                                                                                                                                                                           // 0D5
		virtual void                     Reset();                                                                                                                                                                                                                          // 0D6
		virtual float                    GetLastRenderTime();                                                                                                                                                                                                              // 0D7
		virtual void                     ForceNetRelevant();                                                                                                                                                                                                               // 0D8
		virtual void                     ForceNetUpdate();                                                                                                                                                                                                                 // 0D9
		virtual void                     PrestreamTextures(float a_seconds, bool a_stream, std::int32_t a_cinematicTextureGroups);                                                                                                                                         // 0DA
		virtual void                     GetActorEyesViewPoint(FVector& a_location, FRotator& a_rotation);                                                                                                                                                                 // 0DB
		virtual FVector                  GetTargetLocation(AActor* a_request = nullptr);                                                                                                                                                                                   // 0DC
		virtual void                     PostRenderFor(APlayerController* a_player, UCanvas* a_canvas, FVector a_position, FVector a_direction);                                                                                                                           // 0DD
		virtual UActorComponent*         FindComponentByClass(const TSubclassOf<UActorComponent> a_class);                                                                                                                                                                 // 0DE
		virtual UActorComponent*         FindComponentByInterface(const TSubclassOf<UInterface> a_interface);                                                                                                                                                              // 0DF
		virtual ELifetimeCondition       AllowActorComponentToReplicate(const UActorComponent* a_component);                                                                                                                                                               // 0E0
		virtual bool                     IsComponentRelevantForNavigation(UActorComponent* a_component);                                                                                                                                                                   // 0E1
		virtual void                     DisplayDebug(UCanvas* a_canvas, const FDebugDisplayInfo& a_debugDisplay, float& a_yLine, float& a_yPos);                                                                                                                          // 0E2

		// members
		FActorTickFunction                    primaryActorTick;                                 // 028
		std::uint8_t                          netTemporary: 1;                                  // 058:0
		std::uint8_t                          netStartup: 1;                                    // 058:1
		std::uint8_t                          onlyRelevantToOwner: 1;                           // 058:2
		std::uint8_t                          alwaysRelevant: 1;                                // 058:3
		std::uint8_t                          replicateMovement: 1;                             // 058:4
		std::uint8_t                          callPreReplication: 1;                            // 058:5
		std::uint8_t                          callPreReplicationForReplay: 1;                   // 058:6
		std::uint8_t                          hidden: 1;                                        // 058:7
		std::uint8_t                          tearOff: 1;                                       // 059:0
		std::uint8_t                          forceNetAddressable: 1;                           // 059:1
		std::uint8_t                          exchangedRoles: 1;                                // 059:2
		std::uint8_t                          netLoadOnClient: 1;                               // 059:3
		std::uint8_t                          netUseOwnerRelevancy: 1;                          // 059:4
		std::uint8_t                          relevantForNetworkReplays: 1;                     // 059:5
		std::uint8_t                          relevantForLevelBounds: 1;                        // 059:6
		std::uint8_t                          replayRewindable: 1;                              // 059:7
		std::uint8_t                          allowTickBeforeBeginPlay: 1;                      // 05A:0
		std::uint8_t                          autoDestroyWhenFinished: 1;                       // 05A:1
		std::uint8_t                          canBeDamaged: 1;                                  // 05A:2
		std::uint8_t                          blockInput: 1;                                    // 05A:3
		std::uint8_t                          collideWhenPlacing: 1;                            // 05A:4
		std::uint8_t                          findCameraComponentWhenViewTarget: 1;             // 05A:5
		std::uint8_t                          generateOverlapEventsDuringLevelStreaming: 1;     // 05A:6
		std::uint8_t                          ignoresOriginShifting: 1;                         // 05A:7
		std::uint8_t                          enableAutoLODGeneration: 1;                       // 05B:0
		std::uint8_t                          isEditorOnlyActor: 1;                             // 05B:1
		std::uint8_t                          actorSeamlessTraveled: 1;                         // 05B:2
		std::uint8_t                          replicates: 1;                                    // 05B:3
		std::uint8_t                          canBeInCluster: 1;                                // 05B:4
		std::uint8_t                          allowReceiveTickEventOnDedicatedServer: 1;        // 05B:5
		std::uint8_t                          netCheckedInitialPhysicsState: 1;                 // 05B:6
		std::uint8_t                          replicateUsingRegisteredSubObjectList: 1;         // 05B:7
		std::uint8_t                          hasFinishedSpawning: 1;                           // 05C:0
		std::uint8_t                          actorInitialized: 1;                              // 05C:1
		std::uint8_t                          actorBeginningPlayFromLevelStreaming: 1;          // 05C:2
		std::uint8_t                          tickFunctionsRegistered: 1;                       // 05C:3
		std::uint8_t                          hasDeferredComponentRegistration: 1;              // 05C:4
		std::uint8_t                          runningUserConstructionScript: 1;                 // 05C:5
		std::uint8_t                          hasRegisteredAllComponents: 1;                    // 05C:6
		std::uint8_t                          actorEnableCollision: 1;                          // 05C:7
		std::uint8_t                          actorIsBeingDestroyed: 1;                         // 05D:0
		std::uint8_t                          actorWantsDestroyDuringBeginPlay: 1;              // 05D:1
		EActorBeginPlayState                  actorHasBegunPlay: 2;                             // 05D:2
		std::uint8_t                          actorIsBeingConstructed: 1;                       // 05D:4
		std::uint8_t                          asyncPhysicsTickEnabled: 1;                       // 05D:5
		EActorUpdateOverlapsMethod            updateOverlapsMethodDuringLevelStreaming;         // 05E
		EActorUpdateOverlapsMethod            defaultUpdateOverlapsMethodDuringLevelStreaming;  // 05F
		float                                 initialLifeSpan;                                  // 060
		float                                 customTimeDilation;                               // 064
		TEnumAsByte<ENetRole>                 remoteRole;                                       // 068
		std::int32_t                          rayTracingGroupId;                                // 06C
		FRepAttachment                        attachmentReplication;                            // 070
		FRepMovement                          replicatedMovement;                               // 0D0
		TObjectPtr<AActor>                    owner;                                            // 140
		FName                                 netDriverName;                                    // 148
		TEnumAsByte<ENetRole>                 role;                                             // 150
		TEnumAsByte<ENetDormancy>             netDormancy;                                      // 151
		ESpawnActorCollisionHandlingMethod    spawnCollisionHandlingMethod;                     // 152
		TEnumAsByte<EAutoReceiveInput>        autoReceiveInput;                                 // 153
		std::int32_t                          inputPriority;                                    // 154
		float                                 creationTime;                                     // 158
		TObjectPtr<UInputComponent>           inputComponent;                                   // 15C
		float                                 netCullDistanceSquared;                           // 168
		std::int32_t                          netTag;                                           // 16C
		float                                 netUpdateFrequency;                               // 170
		float                                 minNetUpdateFrequency;                            // 174
		float                                 netPriority;                                      // 178
		EPhysicsReplicationMode               physicsReplicationMode;                           // 17C
		float                                 lastRenderTime;                                   // 180
		TObjectPtr<APawn>                     instigator;                                       // 184
		TArray<TObjectPtr<AActor>>            children;                                         // 190
		TObjectPtr<USceneComponent>           rootComponent;                                    // 1A0
		FTimerHandle                          timerHandle_LifeSpanExpired;                      // 1A8
		TArray<FName>                         layers;                                           // 1B0
		TWeakObjectPtr<UChildActorComponent>  parentComponent;                                  // 1C0
		TArray<FName>                         tags;                                             // 1C8
		std::uint8_t                          onTakeAnyDamage;                                  // 1D8 - FTakeAnyDamageSignature
		std::uint8_t                          onTakePointDamage;                                // 1D9 - FTakePointDamageSignature
		std::uint8_t                          onTakeRadialDamage;                               // 1DA - FTakeRadialDamageSignature
		std::uint8_t                          onActorBeginOverlap;                              // 1DB - FActorBeginOverlapSignature
		std::uint8_t                          onActorEndOverlap;                                // 1DC - FActorEndOverlapSignature
		std::uint8_t                          onBeginCursorOver;                                // 1DD - FActorBeginCursorOverSignature
		std::uint8_t                          onEndCursorOver;                                  // 1DE - FActorEndCursorOverSignature
		std::uint8_t                          onClicked;                                        // 1DF - FActorOnClickedSignature
		std::uint8_t                          onReleased;                                       // 1E0 - FActorOnReleasedSignature
		std::uint8_t                          onInputTouchBegin;                                // 1E1 - FActorOnInputTouchBeginSignature
		std::uint8_t                          onInputTouchEnd;                                  // 1E2 - FActorOnInputTouchEndSignature
		std::uint8_t                          onInputTouchEnter;                                // 1E3 - FActorBeginTouchOverSignature
		std::uint8_t                          onInputTouchLeave;                                // 1E4 - FActorEndTouchOverSignature
		std::uint8_t                          onActorHit;                                       // 1E5 - FActorHitSignature
		std::uint8_t                          onDestroyed;                                      // 1E6 - FActorDestroyedSignature
		std::uint8_t                          onEndPlay;                                        // 1E7 - FActorEndPlaySignature
		std::byte                             replicatedSubObjects[0x10];                       // 1E8 - Net::FSubObjectRegistry
		TArray<Net::FReplicatedComponentInfo> replicatedComponentsInfo;                         // 1F8
		TArray<UActorComponent*>              replicatedComponents;                             // 208
		TSet<TObjectPtr<UActorComponent>>     ownedComponents;                                  // 218
		TArray<TObjectPtr<UActorComponent>>   instanceComponents;                               // 268
		TArray<TObjectPtr<UActorComponent>>   blueprintCreatedComponents;                       // 278
		FRenderCommandFence                   detachFence;                                      // 288
	};
	static_assert(sizeof(AActor) == 0x298);
}
