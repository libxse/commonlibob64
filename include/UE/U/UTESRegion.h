#pragma once

#include "UE/U/UTESForm.h"

namespace UE
{
	class FTESRegionPointList;
	class UTESWorldSpace;

	class UTESRegion :
		public UTESForm
	{
	public:
		UE_DEFINE_UOBJECT(UTESRegion, UTESForm, "Altar", "TESRegion");

		// override
		virtual ~UTESRegion();  // 00

		// members
		TArray<FTESRegionPointList> pointLists;    // 0D8
		UTESWorldSpace*             worldSpace;    // 0E8
		std::uint32_t               worldSpaceID;  // 0F0
	};
	static_assert(sizeof(UTESRegion) == 0x0F8);
}
