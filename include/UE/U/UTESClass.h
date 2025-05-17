#pragma once

#include "UE/U/UTESForm.h"

namespace UE
{
	class UTESClass :
		public UTESForm
	{
	public:
		UE_DEFINE_UOBJECT(UTESClass, UTESForm, "Altar", "TESClass");

		// override
		virtual ~UTESClass();  // 00
	};
	static_assert(sizeof(UTESClass) == 0x0D8);
}
