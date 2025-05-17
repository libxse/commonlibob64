#pragma once

#include "UE/F/FBlueprintCookedComponentInstancingData.h"
#include "UE/I/IBlueprintPropertyGuidProvider.h"
#include "UE/T/TIndirectArray.h"
#include "UE/U/UClass.h"

namespace UE
{
	class UActorComponent;
	class UDynamicBlueprintBinding;
	class UInheritableComponentHandler;
	class USimpleConstructionScript;
	class UStructProperty;
	class UTimelineTemplate;
	class FBPComponentClassOverride;
	class FCustomPropertyListNode;
	class FFieldNotificationId;
	class FStructProperty;

	class UBlueprintGeneratedClass :
		public UClass,
		public IBlueprintPropertyGuidProvider
	{
	public:
		UE_DEFINE_UOBJECT(UBlueprintGeneratedClass, UClass, "Engine", "BlueprintGeneratedClass");

		// override
		virtual ~UBlueprintGeneratedClass();  // 00

		// members
		std::int32_t                                         numReplicatedProperties;                              // 208
		std::uint8_t                                         hasNativizedParent_DEPRECATED: 1;                     // 20C:0
		std::uint8_t                                         hasCookedComponentInstancingData: 1;                  // 20C:1
		std::uint8_t                                         customPropertyListForPostConstructionInitialized: 1;  // 20C:2
		TArray<TObjectPtr<UDynamicBlueprintBinding>>         dynamicBindingObjects;                                // 210
		TArray<TObjectPtr<UActorComponent>>                  componentTemplates;                                   // 220
		TArray<TObjectPtr<UTimelineTemplate>>                timelines;                                            // 230
		TArray<FBPComponentClassOverride>                    componentClassOverrides;                              // 240
		TArray<FFieldNotificationId>                         fieldNotifies;                                        // 250
		std::int32_t                                         fieldNotifiesStartBitNumber;                          // 260
		TObjectPtr<USimpleConstructionScript>                simpleConstructionScript;                             // 268
		TObjectPtr<UInheritableComponentHandler>             inheritableComponentHandler;                          // 270
		TObjectPtr<UStructProperty>                          uberGraphFramePointerProperty_DEPRECATED;             // 278
		FStructProperty*                                     uberGraphFramePointerProperty;                        // 280
		TObjectPtr<UFunction>                                uberGraphFunction;                                    // 288
		TMap<FName, FGuid>                                   cookedPropertyGuids;                                  // 290
		TMap<FName, FBlueprintCookedComponentInstancingData> cookedComponentInstancingData;                        // 2E0
		TIndirectArray<FCustomPropertyListNode>              customPropertyListForPostConstruction;                // 330
		FWindowsCriticalSection                              serializeAndPostLoadCritical;                         // 340
	};
	static_assert(sizeof(UBlueprintGeneratedClass) == 0x368);
}
