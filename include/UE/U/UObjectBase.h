#pragma once

#include "UE/E/EObjectFlags.h"
#include "UE/F/FName.h"

#include "UE/UnrealCore.h"

namespace UE
{
	class UClass;
	class UObject;

	class UObjectBase
	{
	public:
		// add
		virtual ~UObjectBase();  // 00

		// add
		virtual void  RegisterDependencies();                                                                  // 01
		virtual void  DeferredRegister(UClass* a_class, const wchar_t* a_packageName, const wchar_t* a_name);  // 02
		virtual FName GetFNameForStatID() const;                                                               // 03

		UClass* GetClass() const
		{
			return classPrivate;
		}

		FName GetFName() const
		{
			return namePrivate;
		}

		UObject* GetOuter() const
		{
			return outerPrivate;
		}

		// members
		EObjectFlags objectFlags;    // 08
		std::int32_t internalIndex;  // 0C
		UClass*      classPrivate;   // 10
		FName        namePrivate;    // 18
		UObject*     outerPrivate;   // 20
	};
	static_assert(sizeof(UObjectBase) == 0x28);
}
