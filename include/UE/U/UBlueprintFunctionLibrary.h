#pragma once

#include "UE/U/UObject.h"

namespace UE
{
	class UBlueprintFunctionLibrary :
		public UObject
	{
	public:
		UE_DEFINE_UOBJECT(UBlueprintFunctionLibrary, UObject, "Engine", "BlueprintFunctionLibrary");

		// override
		virtual ~UBlueprintFunctionLibrary();  // 00
	};
	static_assert(sizeof(UBlueprintFunctionLibrary) == 0x28);
}
