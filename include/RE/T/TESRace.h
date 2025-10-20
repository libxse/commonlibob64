#pragma once

#include "RE/B/BSTList.h"
#include "RE/F/FR2MatrixVTC.h"
#include "RE/N/NiTArray.h"
#include "RE/R/RACE_DATA.h"
#include "RE/T/TESAttributes.h"
#include "RE/T/TESDescription.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESFullName.h"
#include "RE/T/TESModel.h"
#include "RE/T/TESReactionForm.h"
#include "RE/T/TESSpellList.h"
#include "RE/T/TESTexture.h"

namespace RE
{
	class FaceGenUndo;
	class TESEyes;
	class TESHair;

	class TESRace :
		public TESForm,
		public TESFullName,
		public TESDescription,
		public TESSpellList,
		public TESReactionForm
	{
	public:
		inline static constexpr auto RTTI = RTTI::TESRace;
		inline static constexpr auto VTABLE = VTABLE::TESRace;
		inline static constexpr auto FORMTYPE = FormType::Race;

		// members
		RACE_DATA              data;                    // 0A0
		TESAttributes          maleAttributes;          // 0C8
		TESAttributes          femaleAttributes;        // 0D8
		BSSimpleList<TESHair*> hairList;                // 0E8
		TESHair*               defaultHair[2];          // 0F8
		std::uint8_t           defaultHairColor;        // 108
		float                  clampFaceGeoValue;       // 10C
		float                  clampFaceGeoValue2;      // 110
		BSSimpleList<TESEyes*> eyeList;                 // 118
		TESModel               tailModels[2];           // 128
		TESModel               headModelFiles[9];       // 188
		TESTexture             headTextureFiles[9];     // 338
		TESTexture             bodyTextureFiles[2][5];  // 410
		FR2MatrixVTC<float>    meanFaceCoord[2][2];     // 500
		std::uint16_t          faceCoordNum;            // 580
		TESRace*               voiceRace[2];            // 588
		NiTArray<FaceGenUndo*> faceGenUndoStates;       // 598
	};
	static_assert(sizeof(TESRace) == 0x5B0);
}
