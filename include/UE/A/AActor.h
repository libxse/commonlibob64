#pragma once

#include "UE/E/EAutoReceiveInput.h"
#include "UE/E/ENetDormancy.h"
#include "UE/E/ENetRole.h"
#include "UE/E/EPhysicsReplicationMode.h"
#include "UE/E/ESpawnActorCollisionHandlingMethod.h"
#include "UE/F/FActorTickFunction.h"
#include "UE/F/FRenderCommandFence.h"
#include "UE/F/FRepAttachment.h"
#include "UE/F/FRepMovement.h"
#include "UE/F/FTimerHandle.h"
#include "UE/T/TObjectPtr.h"
#include "UE/T/TWeakObjectPtr.h"
#include "UE/U/UObject.h"

namespace UE::Net
{
	class FReplicatedComponentInfo;
}

namespace UE
{
	class APawn;
	class UActorComponent;
	class UChildActorComponent;
	class UInputComponent;
	class USceneComponent;

	enum class EActorUpdateOverlapsMethod : std::uint8_t
	{
		UseConfigDefault,
		AlwaysUpdate,
		OnlyUpdateMovable,
		NeverUpdate
	};

	enum class ESpawnActorScaleMethod : std::uint8_t
	{
		OverrideRootScale,
		MultiplyWithRoot,
		SelectDefaultAtRuntime,
	};

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
		virtual ~AActor();  // 00

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
