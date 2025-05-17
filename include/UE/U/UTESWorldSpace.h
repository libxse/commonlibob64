#pragma once

#include "UE/F/FVector.h"
#include "UE/F/FWorldMapData.h"
#include "UE/F/FWorldMapLandscapeInfo.h"
#include "UE/F/FWorldMapLandscapeSettings.h"
#include "UE/U/UTESForm.h"

namespace UE
{
	class UTESCell;
	class UTESClimate;
	class UTESTexture;
	class UTESWaterForm;

	class UTESWorldSpace :
		public UTESForm
	{
	public:
		UE_DEFINE_UOBJECT(UTESWorldSpace, UTESForm, "Altar", "TESWorldSpace");

		// override
		virtual ~UTESWorldSpace();

		// members
		FWorldMapLandscapeSettings    landscapeGenerationSettings;  // 0D8
		FWorldMapLandscapeInfo        landscapeGenerationInfo;      // 100
		std::uint8_t                  flags;                        // 160
		TArray<std::int64_t>          cellFileOffsets;              // 168
		UTESClimate*                  climate;                      // 178
		UTESWaterForm*                worldWater;                   // 180
		UTESWorldSpace*               parentWorld;                  // 188
		FWorldMapData                 worldMapData;                 // 190
		FVector                       minimumCoord;                 // 1B0
		FVector                       maximumCoord;                 // 1C8
		UTESTexture*                  texture;                      // 1E0
		TMap<std::int32_t, UTESCell*> cellMap;                      // 1E8
		UTESCell*                     persistentCell;               // 238
		std::uint32_t                 climateLink;                  // 240
		std::uint32_t                 worldWaterLink;               // 244
		std::uint32_t                 parentWorldLink;              // 248
	};
	static_assert(sizeof(UTESWorldSpace) == 0x250);
}
