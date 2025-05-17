#pragma once

#include "UE/E/EClassCastFlags.h"
#include "UE/E/EClassFlags.h"
#include "UE/F/FObjectPostSaveRootContext.h"
#include "UE/F/FObjectPreSaveContext.h"
#include "UE/F/FObjectPreSaveRootContext.h"
#include "UE/F/FString.h"
#include "UE/F/FStructuredArchiveRecord.h"
#include "UE/T/TArray.h"
#include "UE/T/TMap.h"
#include "UE/U/UObjectBaseUtility.h"
#include "UE/UnrealMacro.h"

namespace UE
{
	namespace EDuplicateMode
	{
		enum class Type : std::int8_t;
	}

	namespace Net
	{
		enum class EFragmentRegistrationFlags : std::int8_t;

		class FFragmentRegistrationContext;
	}

	class FArchive;
	class FCustomPropertyConditionState;
	class FFeedbackContext;
	class FFrame;
	class FLifetimeProperty;
	class FObjectDuplicationParameters;
	class FObjectInstancingGraph;
	class FOutParmRec;
	class FOutputDevice;
	class FPrimaryAssetId;
	class FProperty;
	class FRepRecord;
	class FResourceSizeEx;
	class FRestoreForUObjectOverwrite;
	class ITargetPlatform;
	class UFunction;
	class UWorld;

	class UObject :
		public UObjectBaseUtility
	{
	public:
		UE_DEFINE_UOBJECT_INTRINSIC(UObject, UObjectBaseUtility, "CoreUObject", "Object", EClassFlags::Abstract | EClassFlags::Intrinsic, EClassCastFlags::None);

		class FAssetRegistryTag
		{
		public:
			enum class ETagType : std::int32_t;

			// members
			FName         name;          // 00
			FString       value;         // 08
			ETagType      type;          // 18
			std::uint32_t displayFlags;  // 1C
		};
		static_assert(sizeof(FAssetRegistryTag) == 0x20);

		// override
		virtual ~UObject();  // 00

		// add
		virtual FString                      GetDetailedInfoInternal() const;                                                                    // 08
		virtual void                         PostInitProperties();                                                                               // 09
		virtual void                         PostReinitProperties();                                                                             // 0A
		virtual void                         PostCDOContruct();                                                                                  // 0B
		virtual void                         PreSaveRoot(FObjectPreSaveRootContext);                                                             // 0C
		virtual bool                         PreSaveRoot(const wchar_t*);                                                                        // 0D
		virtual void                         PostSaveRoot(FObjectPostSaveRootContext);                                                           // 0E
		virtual void                         PostSaveRoot(bool);                                                                                 // 0F
		virtual void                         PreSave(FObjectPreSaveContext);                                                                     // 10
		virtual void                         PreSave(const ITargetPlatform*);                                                                    // 11
		virtual bool                         ResolveSubobject(const wchar_t*, UObject**, bool);                                                  // 12
		virtual bool                         IsReadyForAsyncPostLoad() const;                                                                    // 13
		virtual void                         PostLoad();                                                                                         // 14
		virtual void                         PostLoadSubobjects(FObjectInstancingGraph*);                                                        // 15
		virtual void                         BeginDestroy();                                                                                     // 16
		virtual bool                         IsReadyForFinishDestroy();                                                                          // 17
		virtual void                         FinishDestroy();                                                                                    // 18
		virtual void                         Serialize(FStructuredArchiveRecord);                                                                // 19
		virtual void                         Serialize(FArchive*);                                                                               // 1A
		virtual void                         ShutdownAfterError();                                                                               // 1B
		virtual void                         PostInterpChange(FProperty*);                                                                       // 1C
		virtual void                         PostRename(UObject*, const FName);                                                                  // 1D
		virtual void                         PreDuplicate(FObjectDuplicationParameters*);                                                        // 1E
		virtual void                         PostDuplicate(EDuplicateMode::Type);                                                                // 1F
		virtual void                         PostDuplicate(bool);                                                                                // 20
		virtual bool                         NeedsLoadForClient() const;                                                                         // 21
		virtual bool                         NeedsLoadForServer() const;                                                                         // 22
		virtual bool                         NeedsLoadForTargetPlatform(const ITargetPlatform*) const;                                           // 23
		virtual bool                         NeedsLoadForEditorGame() const;                                                                     // 24
		virtual bool                         IsEditorOnly() const;                                                                               // 25
		virtual bool                         HasNonEditorOnlyReferences() const;                                                                 // 26
		virtual bool                         IsPostLoadThreadSafe() const;                                                                       // 27
		virtual bool                         IsDestructionThreadSafe() const;                                                                    // 28
		virtual void                         GetPreloadDependencies(TArray<UObject*>*);                                                          // 29
		virtual void                         GetPrestreamPackages(TArray<UObject*>*);                                                            // 2A
		virtual void                         ExportCustomProperties(FOutputDevice*, std::uint32_t);                                              // 2B
		virtual void                         ImportCustomProperties(const wchar_t*, FFeedbackContext*);                                          // 2C
		virtual void                         PostEditImport();                                                                                   // 2D
		virtual void                         PostReloadConfig(FProperty*);                                                                       // 2E
		virtual bool                         Rename(const wchar_t*, UObject*, std::uint32_t);                                                    // 2F
		virtual FString                      GetDesc();                                                                                          // 30
		virtual UWorld*                      GetWorld() const;                                                                                   // 31
		virtual bool                         GetNativePropertyValues(TMap<FString, FString>*, std::uint32_t) const;                              // 32
		virtual void                         GetResourceSizeEx(FResourceSizeEx*);                                                                // 33
		virtual FName                        GetExporterName();                                                                                  // 34
		virtual FRestoreForUObjectOverwrite* GetRestoreForUObjectOverwrite();                                                                    // 35
		virtual bool                         AreNativePropertiesIdenticalTo(UObject* a_other) const;                                             // 36
		virtual void                         GetAssetRegistryTags(TArray<UObject::FAssetRegistryTag>*) const;                                    // 37
		virtual void                         GetExternalActorExtendedAssetRegistryTags(TArray<UObject::FAssetRegistryTag>*) const;               // 38
		virtual bool                         IsAsset() const;                                                                                    // 39
		virtual FPrimaryAssetId*             GetPrimaryAssetId() const;                                                                          // 3A
		virtual bool                         IsLocalizedResource() const;                                                                        // 3B
		virtual bool                         IsSafeForRootSet() const;                                                                           // 3C
		virtual void                         TagSubobjects(EObjectFlags);                                                                        // 3D
		virtual void                         GetLifetimeReplicatedProps(TArray<FLifetimeProperty>*) const;                                       // 3E
		virtual void                         GetReplicatedCustomConditionState(FCustomPropertyConditionState*) const;                            // 3F
		virtual void                         RegisterReplicationFragments(Net::FFragmentRegistrationContext*, Net::EFragmentRegistrationFlags);  // 40
		virtual bool                         IsNameStableForNetworking() const;                                                                  // 41
		virtual bool                         IsFullNameStableForNetworking() const;                                                              // 42
		virtual bool                         IsSupportedForNetworking() const;                                                                   // 43
		virtual void                         GetSubobjectsWithStableNamesForNetworking(TArray<UObject*>*);                                       // 44
		virtual void                         PreNetReceive();                                                                                    // 45
		virtual void                         PostNetReceive();                                                                                   // 46
		virtual void                         PostRepNotifies();                                                                                  // 47
		virtual void                         PreDestroyFromReplication();                                                                        // 48
		virtual void                         BuildSubobjectMapping(UObject*, TMap<UObject*, UObject*>*) const;                                   // 49
		virtual const wchar_t*               GetConfigOverridePlatform() const;                                                                  // 4A
		virtual void                         OverrideConfigSection(FString&);                                                                    // 4B
		virtual void                         OverridePerObjectConfigSection(FString&);                                                           // 4C
		virtual void                         ProcessEvent(UFunction* a_function, void* a_params);                                                // 4D
		virtual int                          GetFunctionCallspace(UFunction* a_function, FFrame* a_stack);                                       // 4E
		virtual bool                         CallRemoteFunction(UFunction*, void*, FOutParmRec*, FFrame*);                                       // 4F
		virtual bool                         ProcessConsoleExec(const wchar_t* a_cmd, FOutputDevice* a_ar, UObject* a_executor);                 // 50
		virtual UClass*                      RegenerateClass(UClass*, UObject*);                                                                 // 51
		virtual void                         MarkAsEditorOnlySubobject();                                                                        // 52
		virtual bool                         CheckDefaultSubobjectsInternal() const;                                                             // 53
		virtual void                         ValidateGeneratedRepEnums(const TArray<FRepRecord>*) const;                                         // 54
		virtual void                         SetNetPushIdDynamic(const std::uint64_t a_id);                                                      // 55
		virtual std::uint64_t                GetNetPushIdDynamic() const;                                                                        // 56

		FString GetDetailedInfo() const
		{
			return this ? GetDetailedInfoInternal() : L"None";
		}
	};
	static_assert(sizeof(UObject) == 0x28);
}
