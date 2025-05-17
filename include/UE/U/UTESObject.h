#pragma once

#include "UE/U/UTESForm.h"

namespace UE
{
	class UTESObject :
		public UTESForm
	{
	public:
		UE_DEFINE_UOBJECT(UTESObject, UTESForm, "Altar", "TESObject");

		// override
		virtual ~UTESObject();  // 00
	};
	static_assert(sizeof(UTESObject) == 0x0D8);
}
