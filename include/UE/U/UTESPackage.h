#pragma once

#include "UE/U/UTESForm.h"

namespace UE
{
	class UTESPackage :
		public UTESForm
	{
	public:
		UE_DEFINE_UOBJECT(UTESPackage, UTESForm, "Altar", "TESPackage");

		// override
		virtual ~UTESPackage();  // 00
	};
	static_assert(sizeof(UTESPackage) == 0x0D8);
}
