#pragma once

#include "UE/E/EClassCastFlags.h"
#include "UE/E/EClassFlags.h"
#include "UE/F/FRWLock.h"
#include "UE/U/UStruct.h"

namespace UE
{
	class FImplementedInterface;
	class FNativeFunctionLookup;
	class FObjectInitializer;
	class FVTableHelper;
	class UScriptStruct;

	enum class EIncludeSuperFlag : std::int32_t
	{
		ExcludeSuper,
		IncludeSuper
	};

	using FUClassFuncLock = FRWLock;

	class UClass :
		public UStruct
	{
	public:
		UE_DEFINE_UOBJECT_INTRINSIC(UClass, UStruct, "CoreUObject", "Class", EClassFlags::None, EClassCastFlags::UClass);

		// override
		virtual ~UClass();

		// add
		virtual UClass*       GetAuthoritativeClass();                                                                                                                                 // 6C
		virtual void          PostInitInstance(UObject* a_object, FObjectInstancingGraph* a_instanceGraph);                                                                            // 6D
		virtual void          PostLoadInstance(UObject* a_object);                                                                                                                     // 6F
		virtual void          InitPropertiesFromCustomList(std::uint8_t* a_dataPtr, const std::uint8_t* a_defaultDataPtr);                                                             // 70
		virtual void          SetupObjectInitializer(FObjectInitializer& a_objectInitializer) const;                                                                                   // 71
		virtual bool          CanCreateAssetOfClass() const;                                                                                                                           // 72
		virtual std::uint8_t* GetPersistentUberGraphFrame(UObject* a_object, UFunction* a_funcToCheck) const;                                                                          // 73
		virtual void          CreatePersistentUberGraphFrame(UObject* a_object, bool a_createOnlyIfEmpty = false, bool a_skipSuperClass = false, UClass* a_oldClass = nullptr) const;  // 74
		virtual void          DestroyPersistentUberGraphFrame(UObject* a_object, bool a_skipSuperClass = false) const;                                                                 // 75
		virtual void          SerializeDefaultObject(UObject* a_object, FStructuredArchive::FSlot a_slot);                                                                             // 76
		virtual void          SerializeDefaultObject(UObject* a_object, FArchive& a_archive);                                                                                          // 77
		virtual void          PostLoadDefaultObject(UObject* a_object);                                                                                                                // 78
		virtual void          PurgeClass(bool a_recompilingOnLoad);                                                                                                                    // 79
		virtual bool          IsFunctionImplementedInScript(FName a_name) const;                                                                                                       // 7A
		virtual bool          HasProperty(FProperty* a_property) const;                                                                                                                // 7B
		virtual UObject*      FindArchetype(const UClass* a_class, const FName a_name) const;                                                                                          // 7C
		virtual UObject*      GetArchetypeForCDO() const;                                                                                                                              // 7D
		virtual void          GetDefaultObjectPreloadDependencies(TArray<UObject*>& a_deps);                                                                                           // 7E
		virtual UObject*      CreateDefaultObject();                                                                                                                                   // 7F

		UFunction* FindFunctionByName(FName a_name, EIncludeSuperFlag a_includeSuper = EIncludeSuperFlag::IncludeSuper) const
		{
			using func_t = UFunction* (UClass::*)(FName, EIncludeSuperFlag) const;
			static REL::Relocation<func_t> func{ ID::UClass::FindFunctionByName };
			return func(this, a_name, a_includeSuper);
		}

		EClassFlags GetClassFlags() const
		{
			return classFlags;
		}

		FTopLevelAssetPath GetClassPathName() const
		{
			return GetStructPathName();
		}

		UObject* GetDefaultObject(bool a_create = true) const
		{
			if (!classDefaultObject && a_create)
				const_cast<UClass*>(this)->CreateDefaultObject();

			return classDefaultObject;
		}

		template <class T>
		T* GetDefaultObject(bool a_create = true) const
		{
			return static_cast<T*>(GetDefaultObject(a_create));
		}

		UClass* GetSuperClass() const
		{
			return static_cast<UClass*>(GetSuperStruct());
		}

		bool HasAnyCastFlag(EClassCastFlags a_flag) const
		{
			return !!(classCastFlags & a_flag);
		}

		bool HasAllCastFlags(EClassCastFlags a_flag) const
		{
			return (classCastFlags & a_flag) == a_flag;
		}

		// members
		std::uintptr_t                     classConstructor;             // 0B0
		std::uintptr_t                     classVTableHelperCtorCaller;  // 0B8
		std::byte                          unkC0[0x8];                   // 0C0
		mutable std::int32_t               classUnique;                  // 0C8
		std::int32_t                       firstOwnedClassRep;           // 0CC
		bool                               cooked;                       // 0D0
		bool                               layoutChanging;               // 0D1
		EClassFlags                        classFlags;                   // 0D4
		EClassCastFlags                    classCastFlags;               // 0D8
		TObjectPtr<UClass>                 classWithin;                  // 0E0
		FName                              classConfigName;              // 0E8
		TArray<FRepRecord>                 classReps;                    // 0F0
		TArray<UField*>                    netFields;                    // 100
		TObjectPtr<UObject>                classDefaultObject;           // 110
		void*                              sparseClassData;              // 118
		TObjectPtr<UScriptStruct>          sparseClassDataStruct;        // 120
		TMap<FName, TObjectPtr<UFunction>> funcMap;                      // 128
		mutable FUClassFuncLock            funcMapLock;                  // 178
		mutable TMap<FName, UFunction*>    allFunctionsCache;            // 180
		mutable FUClassFuncLock            allFunctionsCacheLock;        // 1D0
		TArray<FImplementedInterface>      interfaces;                   // 1D8
		std::uint64_t                      referenceSchema;              // 1E8 - GC::FSchemaOwner
		TArray<FNativeFunctionLookup>      nativeFunctionLookupTable;    // 1F0
	};
	static_assert(sizeof(UClass) == 0x200);
}
