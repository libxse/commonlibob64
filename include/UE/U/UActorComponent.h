#pragma once

#include "UE/E/EComponentCreationMethod.h"
#include "UE/E/EEndPlayReason.h"
#include "UE/E/ELifetimeCondition.h"
#include "UE/E/ETeleportType.h"
#include "UE/E/EUpdateTransformFlags.h"
#include "UE/F/FActorComponentTickFunction.h"
#include "UE/F/FTypedElementHandle.h"
#include "UE/I/IInterface_AssetUserData.h"
#include "UE/T/TBaseDynamicMulticastDelegate.h"
#include "UE/T/TSparseDynamicDelegate.h"
#include "UE/T/TStructOnScope.h"

namespace UE
{
	class AActor;
	class FActorComponentActivatedSignatureInfoGetter;
	class FActorComponentDeactivateSignatureInfoGetter;
	class FActorComponentInstanceData;
	class FOutBunch;
	class FRegisterComponentContext;
	class IRepChangedPropertyTracker;
	class FReplicationFlags;
	class UActorChannel;

	using FActorComponentActivatedSignature_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, UActorComponent*, bool>;
	using FActorComponentActivatedSignature = TSparseDynamicDelegate<FActorComponentActivatedSignature_MCSignature, UActorComponent, FActorComponentActivatedSignatureInfoGetter>;
	using FActorComponentDeactivateSignature_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, UActorComponent*>;
	using FActorComponentDeactivateSignature = TSparseDynamicDelegate<FActorComponentDeactivateSignature_MCSignature, UActorComponent, FActorComponentDeactivateSignatureInfoGetter>;

	class UActorComponent :
		public UObject,
		public IInterface_AssetUserData
	{
	public:
		UE_DEFINE_UOBJECT(UActorComponent, UObject, "Engine", "ActorComponent");

		// override
		virtual ~UActorComponent();  // 000

		// add
		virtual void                                        OnRep_IsActive();                                                                                      // 057
		virtual void                                        Activate(bool a_reset = false);                                                                        // 058
		virtual void                                        Deactivate();                                                                                          // 059
		virtual void                                        SetActive(bool a_new, bool a_reset = false);                                                           // 05A
		virtual void                                        ToggleActive();                                                                                        // 05B
		virtual void                                        SetAutoActivate(bool a_new);                                                                           // 05C
		virtual bool                                        ReplicateSubobjects(UActorChannel* a_channel, FOutBunch* a_bunch, FReplicationFlags* a_flags);         // 05D
		virtual ELifetimeCondition                          GetReplicationCondition() const;                                                                       // 05E
		virtual void                                        PreReplication(IRepChangedPropertyTracker& a_tracker);                                                 // 05F
		virtual bool                                        GetComponentClassCanReplicate() const;                                                                 // 060
		virtual void                                        OnEndOfFrameUpdateDuringTick();                                                                        // 061
		virtual void                                        OnPreEndOfFrameSync();                                                                                 // 062
		virtual void                                        BeginReplication();                                                                                    // 063
		virtual void                                        EndReplication();                                                                                      // 064
		virtual bool                                        ShouldActivate() const;                                                                                // 065
		virtual void                                        OnRegister();                                                                                          // 066
		virtual void                                        OnUnregister();                                                                                        // 067
		virtual bool                                        ShouldCreateRenderState() const;                                                                       // 068
		virtual void                                        CreateRenderState_Concurrent(FRegisterComponentContext* a_context);                                    // 069
		virtual void                                        SendRenderTransform_Concurrent();                                                                      // 06A
		virtual void                                        SendRenderDynamicData_Concurrent();                                                                    // 06B
		virtual void                                        SendRenderInstanceData_Concurrent();                                                                   // 06C
		virtual void                                        DestroyRenderState_Concurrent();                                                                       // 06D
		virtual void                                        OnCreatePhysicsState();                                                                                // 06E
		virtual void                                        OnDestroyPhysicsState();                                                                               // 06F
		virtual bool                                        ShouldCreatePhysicsState() const;                                                                      // 070
		virtual bool                                        HasValidPhysicsState() const;                                                                          // 071
		virtual void                                        RegisterComponentTickFunctions(bool a_register);                                                       // 072
		virtual void                                        InitializeComponent();                                                                                 // 073
		virtual void                                        ReadyForReplication();                                                                                 // 074
		virtual void                                        BeginPlay();                                                                                           // 075
		virtual void                                        EndPlay(const EEndPlayReason a_reason);                                                                // 076
		virtual void                                        UninitializeComponent();                                                                               // 077
		virtual void                                        TickComponent(float a_deltaTime, ELevelTick a_tickType, FActorComponentTickFunction* a_tickFunction);  // 078
		virtual void                                        AsyncPhysicsTickComponent(float a_deltaTime, float a_simTime);                                         // 079
		virtual void                                        SetComponentTickEnabled(bool a_enabled);                                                               // 07A
		virtual void                                        SetComponentTickEnabledAsync(bool a_enabled);                                                          // 07B
		virtual bool                                        IsComponentTickEnabled() const;                                                                        // 07C
		virtual bool                                        IsReadyForOwnerToAutoDestroy() const;                                                                  // 07D
		virtual void                                        InvalidateLightingCacheDetailed(bool a_queued, bool a_translation);                                    // 07E
		virtual void                                        UpdateComponentToWorld(EUpdateTransformFlags a_flags, ETeleportType a_teleport);                       // 07F
		virtual bool                                        RequiresGameThreadEndOfFrameUpdates() const;                                                           // 080
		virtual bool                                        RequiresGameThreadEndOfFrameRecreate() const;                                                          // 081
		virtual bool                                        RequiresPreEndOfFrameSync() const;                                                                     // 082
		virtual void                                        OnActorEnableCollisionChanged();                                                                       // 083
		virtual FString                                     GetReadableName() const;                                                                               // 084
		virtual const UObject*                              AdditionalStatObject() const;                                                                          // 085
		virtual TStructOnScope<FActorComponentInstanceData> GetComponentInstanceData();                                                                            // 086
		virtual void                                        PostApplyToComponent();                                                                                // 087
		virtual void                                        GetComponentChildElements(TArray<FTypedElementHandle>& a_handles, const bool a_create = true);         // 088
		virtual void                                        DestroyComponent(bool a_promoteChildren);                                                              // 089
		virtual void                                        OnComponentCreated();                                                                                  // 08A
		virtual void                                        OnComponentDestroyed(bool a_hierarchy);                                                                // 08B
		virtual void                                        AddTickPrerequisiteActor(AActor* a_actor);                                                             // 08C
		virtual void                                        AddTickPrerequisiteComponent(UActorComponent* a_component);                                            // 08D
		virtual void                                        RemoveTickPrerequisiteActor(AActor* a_actor);                                                          // 08E
		virtual void                                        RemoveTickPrerequisiteComponent(UActorComponent* a_component);                                         // 08F
		virtual void                                        ApplyWorldOffset(const FVector& a_offset, bool a_shift);                                               // 090
		virtual bool                                        IsNavigationRelevant();                                                                                // 091
		virtual bool                                        IsHLODRelevant();                                                                                      // 092

		// members
		FActorComponentTickFunction        primaryComponentTick;                      // 030
		TArray<FName>                      componentTags;                             // 060
		TArray<TObjectPtr<UAssetUserData>> assetUserData;                             // 070
		std::int32_t                       markedForEndOfFrameUpdateArrayIndex;       // 080
		std::int32_t                       ucsSerializationIndex;                     // 084
		std::uint8_t                       registered: 1;                             // 088:0
		std::uint8_t                       renderStateCreated: 1;                     // 088:1
		std::uint8_t                       physicsStateCreated: 1;                    // 088:2
		std::uint8_t                       netAddressable: 1;                         // 088:3
		std::uint8_t                       replicateUsingRegisteredSubObjectList: 1;  // 088:4
		std::uint8_t                       replicates: 1;                             // 088:5
		std::uint8_t                       renderStateDirty: 1;                       // 088:6
		std::uint8_t                       renderTransformDirty: 1;                   // 088:7
		std::uint8_t                       renderDynamicDataDirty: 1;                 // 089:1
		std::uint8_t                       renderInstancesDirty: 1;                   // 089:2
		std::uint8_t                       routedPostRename: 1;                       // 089:3
		std::uint8_t                       autoRegister: 1;                           // 089:4
		std::uint8_t                       allowReregistration: 1;                    // 089:5
		std::uint8_t                       tickInEditor: 1;                           // 089:6
		std::uint8_t                       neverNeedsRenderUpdate: 1;                 // 089:7
		std::uint8_t                       allowConcurrentTick: 1;                    // 08A:0
		std::uint8_t                       allowAnyoneToDestroyMe: 1;                 // 08A:1
		std::uint8_t                       autoActivate: 1;                           // 08A:2
		std::uint8_t                       isActive: 1;                               // 08A:3
		std::uint8_t                       editableWhenInherited: 1;                  // 08A:4
		std::uint8_t                       navigationRelevant: 1;                     // 08A:5
		std::uint8_t                       canEverAffectNavigation: 1;                // 08A:6
		std::uint8_t                       wantsInitializeComponent: 1;               // 08A:7
		std::uint8_t                       isEditorOnly: 1;                           // 08B:0
		std::uint8_t                       hasBeenCreated: 1;                         // 08B:1
		std::uint8_t                       hasBeenInitialized: 1;                     // 08B:2
		std::uint8_t                       isReadyForReplication: 1;                  // 08B:3
		std::uint8_t                       hasBegunPlay: 1;                           // 08B:4
		std::uint8_t                       isBeingDestroyed: 1;                       // 08B:5
		std::uint8_t                       tickFunctionsRegistered: 1;                // 08B:6
		std::uint8_t                       isNetStartupComponent: 1;                  // 08B:7
		std::uint8_t                       markedForEndOfFrameUpdateState: 2;         // 08C:0
		std::uint8_t                       markedForPreEndOfFrameSync: 1;             // 08C:2
		std::uint8_t                       asyncPhysicsTickEnabled: 1;                // 08C:3
		EComponentCreationMethod           creationMethod;                            // 08D
		FActorComponentActivatedSignature  onComponentActivated;                      // 08E
		FActorComponentDeactivateSignature onComponentDeactivated;                    // 08F
		AActor*                            ownerPrivate;                              // 090
		UWorld*                            worldPrivate;                              // 098
	};
	static_assert(sizeof(UActorComponent) == 0x0A0);
}
