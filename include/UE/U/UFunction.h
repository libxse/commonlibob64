#pragma once

#include "UE/E/EFunctionFlags.h"
#include "UE/U/UInterface.h"
#include "UE/U/UStruct.h"

namespace UE
{
	using FNativeFuncPtr = void (*)(UObject*, FFrame&, const void*);

	class UFunction :
		public UStruct
	{
	public:
		UE_DEFINE_UOBJECT_INTRINSIC(UFunction, UStruct, "CoreUObject", "Function", EClassFlags::None, EClassCastFlags::UFunction);

		// override
		virtual ~UFunction();

		UFunction* GetSuperFunction() const
		{
			UStruct* result = GetSuperStruct();
			assert(!result || result->IsA<UFunction>());
			return static_cast<UFunction*>(result);
		}

		// members
		EFunctionFlags functionFlags;
		std::uint8_t   numParms;
		std::uint16_t  parmsSize;
		std::uint16_t  returnValueOffset;
		std::uint16_t  rpcId;
		std::uint16_t  rpcResponseId;
		FProperty*     firstPropertyToInit;
		UFunction*     eventGraphFunction;
		std::int32_t   eventGraphCallOffset;
		FNativeFuncPtr func;
	};
	static_assert(sizeof(UFunction) == 0xE0);
}
