#pragma once

#include "UE/F/FCellExteriorData.h"
#include "UE/F/FCellInteriorData.h"
#include "UE/U/UTESForm.h"

namespace UE
{
	class UATMPreset;
	class UTESLandscape;
	class UTESPathGrid;
	class UTESWorldSpace;

	class UTESCell :
		public UTESForm
	{
	public:
		UE_DEFINE_UOBJECT(UTESCell, UTESForm, "Altar", "TESCell");

		// override
		virtual ~UTESCell();  // 00

		// members
		FCellInteriorData interiorCellData;  // 0D8
		FCellExteriorData exteriorCellData;  // 118
		std::uint8_t      cellFlags;         // 120
		UTESWorldSpace*   worldSpace;        // 128
		UTESPathGrid*     pathGrid;          // 130
		UTESLandscape*    landscape;         // 138
	};
	static_assert(sizeof(UTESCell) == 0x140);
}
