#pragma once

#include "UE/U/UObject.h"

namespace UE
{
	class UInterface :
		public UObject
	{
	public:
		UE_DEFINE_UOBJECT_INTRINSIC(UInterface, UObject, "CoreUObject", "Interface", EClassFlags::Interface | EClassFlags::Abstract, EClassCastFlags::None);

		// override
		virtual ~UInterface();  // 00
	};
}
