#pragma once

#include "UE/E/EInternalObjectFlags.h"
#include "UE/E/EObjectFullNameFlags.h"
#include "UE/F/FUObjectArray.h"
#include "UE/U/UObjectBase.h"
#include "UE/U/UObjectGlobals.h"

namespace UE
{
	class UObjectBaseUtility :
		public UObjectBase
	{
	public:
		// override
		virtual ~UObjectBaseUtility();  // 00

		// add
		virtual bool CanBeClusterRoot() const;        // 04
		virtual bool CanBeInCluster() const;          // 05
		virtual void CreateCluster();                 // 06
		virtual void OnClusterMarkedAsPendingKill();  // 07

		EObjectFlags GetFlags() const
		{
			return (EObjectFlags)GetFlagsInternal();
		}

		std::int32_t GetFlagsInternal() const
		{
			return (std::int32_t)objectFlags;
		}

		FString GetFullName(const UObject* a_stopOuter = nullptr, EObjectFullNameFlags a_flags = EObjectFullNameFlags::None) const
		{
			using func_t = FString (UObjectBaseUtility::*)(const UObject*, EObjectFullNameFlags) const;
			static REL::Relocation<func_t> func{ ID::UObjectBaseUtility::GetFullName1 };
			return func(this, a_stopOuter, a_flags);
		}

		void GetFullName(const UObject* a_stopOuter, FString& a_str, EObjectFullNameFlags a_flags = EObjectFullNameFlags::None) const
		{
			using func_t = void (UObjectBaseUtility::*)(const UObject*, FString&, EObjectFullNameFlags) const;
			static REL::Relocation<func_t> func{ ID::UObjectBaseUtility::GetFullName2 };
			func(this, a_stopOuter, a_str, a_flags);
		}

		EInternalObjectFlags GetInternalFlags() const
		{
			const auto objects = FUObjectArray::GetSingleton();
			return objects->IndexToObject(internalIndex)->GetFlags();
		}

		FString GetName() const
		{
			return GetFName().ToString();
		}

		bool HasAnyFlags(EObjectFlags a_flags) const
		{
			return !!(GetFlags() & a_flags);
		}

		bool HasAllFlags(EObjectFlags a_flags) const
		{
			return ((GetFlags() & a_flags) == a_flags);
		}

		bool HasAnyInternalFlags(EInternalObjectFlags a_flags) const
		{
			const auto objects = FUObjectArray::GetSingleton();
			return objects->IndexToObject(internalIndex)->HasAnyFlags(a_flags);
		}

		template <class T>
		static bool IsChildOf(const T* a_classA, const T* a_classB)
		{
			a_classA->IsChildOf(a_classB);
		}

		template <class T>
		bool IsA(const T* a_class) const
		{
			return IsChildOf(GetClass(), a_class);
		}

		template <class T>
		bool IsA() const
		{
			return IsA(FindClass<T>());
		}
	};
	static_assert(sizeof(UObjectBaseUtility) == 0x28);
}
