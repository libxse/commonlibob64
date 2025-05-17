#pragma once

#include "UE/U/UTESForm.h"

namespace UE
{
	class UTESTopic :
		public UTESForm
	{
	public:
		UE_DEFINE_UOBJECT(UTESTopic, UTESForm, "Altar", "TESTopic");

		// override
		virtual ~UTESTopic();  // 00
	};
	static_assert(sizeof(UTESTopic) == 0x0D8);
}
