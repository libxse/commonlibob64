#pragma once

#include "UE/U/UTESForm.h"
#include "UE/V/VPairingData_VTransform.h"

namespace UE
{
	class UTESBoundObject;
	class UTESCell;

	class FOBJ_REFR
	{
	public:
		// members
		UTESBoundObject*         objectReference;  // 00
		VPairingData::VTransform transform;        // 08
	};
	static_assert(sizeof(FOBJ_REFR) == 0x50);

	class UTESObjectREFR :
		public UTESForm
	{
	public:
		UE_DEFINE_UOBJECT(UTESObjectREFR, UTESForm, "Altar", "TESObjectREFR");

		// override
		virtual ~UTESObjectREFR();  // 00

		// members
		FOBJ_REFR data;        // 0D8
		float     refScale;    // 128
		UTESCell* parentCell;  // 130
	};
	static_assert(sizeof(UTESObjectREFR) == 0x138);
}
