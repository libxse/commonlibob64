#pragma once

#include "UE/U/UObject.h"

namespace UE
{
	class UField :
		public UObject
	{
	public:
		UE_DEFINE_UOBJECT_INTRINSIC(UField, UObject, "CoreUObject", "Field", EClassFlags::Abstract, EClassCastFlags::UStruct);

		// override
		virtual ~UField();

		// add
		virtual void AddCppProperty(FProperty* a_property);  // 57
		virtual void Bind();                                 // 58

		// members
		UField* next;  // 28
	};
	static_assert(sizeof(UField) == 0x30);
}
