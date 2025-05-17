#pragma once

#include "UE/E/EVBloodColor.h"
#include "UE/F/FOblivionNPCFaceGenData.h"
#include "UE/F/FRaceData.h"
#include "UE/U/UTESForm.h"

namespace UE
{
	class FRaceBody;

	class UTESRace :
		public UTESForm
	{
	public:
		UE_DEFINE_UOBJECT(UTESRace, UTESForm, "Altar", "TESRace");

		// override
		virtual ~UTESRace();  // 00

		// members
		FString                 fullName;                 // 0D8
		FOblivionNPCFaceGenData meanOblivionFaceGenData;  // 0E8
		EVBloodColor            bloodColor;               // 118
		FRaceData               data;                     // 120
		TArray<FRaceBody>       maleFullBodies;           // 130
		TArray<FRaceBody>       femaleFullBodies;         // 140
	};
	static_assert(sizeof(UTESRace) == 0x150);
}
