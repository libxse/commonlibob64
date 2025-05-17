#pragma once

#include "UE/E/EExprToken.h"
#include "UE/F/FGuid.h"
#include "UE/F/FStructBaseChain.h"
#include "UE/F/FStructuredArchive.h"
#include "UE/F/FTopLevelAssetPath.h"
#include "UE/T/TArray.h"
#include "UE/T/TFieldPath.h"
#include "UE/T/TObjectPtr.h"
#include "UE/T/TTuple.h"
#include "UE/U/UField.h"

namespace UE
{
	class FField;
	class FProperty;

	struct FUnversionedStructSchema;

	class UStruct :
		public UField,
		public FStructBaseChain
	{
	public:
		UE_DEFINE_UOBJECT_INTRINSIC(UStruct, UField, "CoreUObject", "Struct", EClassFlags::MatchedSerializers, EClassCastFlags::UStruct);

		// override
		virtual ~UStruct();

		// add
		virtual UStruct*       GetInheritanceSuper() const;                                                                                                                                                                         // 59
		virtual void           Link(FArchive& a_archive, bool a_relinkExistingProperties);                                                                                                                                          // 5A
		virtual void           SerializeBin(FArchive& a_archive, void* a_data) const;                                                                                                                                               // 5B
		virtual void           SerializeBin(FStructuredArchive::FSlot a_slot, void* a_data) const;                                                                                                                                  // 5C
		virtual void           SerializeTaggedProperties(FArchive& a_archive, std::uint8_t* a_data, UStruct* a_defaultsStruct, std::uint8_t* a_defaults, const UObject* a_breakRecursionIfFullyLoad = nullptr) const;               // 5D
		virtual void           SerializeTaggedProperties(FStructuredArchive::FSlot a_slot, std::uint8_t* a_data, UStruct* a_defaultsStruct, std::uint8_t* a_defaults, const UObject* a_breakRecursionIfFullyLoad = nullptr) const;  // 5E
		virtual void           PreloadChildren(FArchive& a_archive);                                                                                                                                                                // 5F
		virtual void           InitializeStruct(void* a_dest, std::int32_t a_arrayDim = 1) const;                                                                                                                                   // 60
		virtual void           DestroyStruct(void* a_dest, std::int32_t a_arrayDim = 1) const;                                                                                                                                      // 61
		virtual FProperty*     CustomFindProperty(const FName a_name) const;                                                                                                                                                        // 62
		virtual EExprToken     SerializeExpr(std::int32_t& a_code, FArchive& a_archive);                                                                                                                                            // 63
		virtual const wchar_t* GetPrefixCPP() const;                                                                                                                                                                                // 64
		virtual void           SetSuperStruct(UStruct* a_struct);                                                                                                                                                                   // 65
		virtual FString        GetAuthoredNameForField(const UField* a_field) const;                                                                                                                                                // 66
		virtual FString        GetAuthoredNameForField(const FField* a_field) const;                                                                                                                                                // 67
		virtual bool           IsStructTrashed() const;                                                                                                                                                                             // 68
		virtual FName          FindPropertyNameFromGuid(const FGuid& a_guid) const;                                                                                                                                                 // 69
		virtual FGuid          FindPropertyGuidFromName(const FName a_name) const;                                                                                                                                                  // 6A
		virtual bool           ArePropertyGuidsAvailable() const;                                                                                                                                                                   // 6B

		FTopLevelAssetPath GetStructPathName() const
		{
			return FTopLevelAssetPath(GetOuter()->GetFName(), GetFName());
		}

		UStruct* GetSuperStruct() const
		{
			return superStruct;
		}

		bool IsChildOf(const UStruct* a_base) const
		{
			return a_base ? IsChildOfUsingStructArray(*a_base) : false;
		}

		template <class T>
		bool IsChildOf() const
		{
			return IsChildOf(FindClass<T>());
		}

		// members
		UStruct*                                          superStruct;                        // 40
		TObjectPtr<UField>                                children;                           // 48
		FField*                                           childProperties;                    // 50
		std::int32_t                                      propertiesSize;                     // 58
		std::int32_t                                      minAlignment;                       // 5C
		TArray<std::uint8_t>                              script;                             // 60
		FProperty*                                        proprtyLink;                        // 70
		FProperty*                                        refLink;                            // 78
		FProperty*                                        destructorLink;                     // 80
		FProperty*                                        postConstructLink;                  // 88
		TArray<TObjectPtr<UObject>>                       scriptAndPropertyObjectReferences;  // 90
		TArray<TTuple<TFieldPath<FField>, std::int32_t>>* unresolvedScriptProperties;         // A0
		mutable const FUnversionedStructSchema*           unversionedGameSchema{ nullptr };   // A8
	};
	static_assert(sizeof(UStruct) == 0xB0);
}
