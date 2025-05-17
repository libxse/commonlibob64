#pragma once

#include "UE/U/UTESForm.h"

namespace UE
{
	class UAnimSequenceBase;

	class UTESIdleForm :
		public UTESForm
	{
	public:
		UE_DEFINE_UOBJECT(UTESIdleForm, UTESForm, "Altar", "TESIdleForm");

		// override
		virtual ~UTESIdleForm();  // 00

		// members
		TSoftObjectPtr<UAnimSequenceBase> animSequence;  // 0D8
		FString                           originalPath;  // 100
	};
	static_assert(sizeof(UTESIdleForm) == 0x110);
}
