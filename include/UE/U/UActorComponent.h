#pragma once

#include "UE/E/EComponentCreationMethod.h"
#include "UE/F/FActorComponentTickFunction.h"
#include "UE/I/IInterface_AssetUserData.h"
#include "UE/T/TBaseDynamicMulticastDelegate.h"
#include "UE/T/TSparseDynamicDelegate.h"

namespace UE
{
	class AActor;
	class FActorComponentActivatedSignatureInfoGetter;
	class FActorComponentDeactivateSignatureInfoGetter;

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
		virtual ~UActorComponent();  // 00

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
