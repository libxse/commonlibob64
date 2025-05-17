#pragma once

#include "UE/U/UTESForm.h"

namespace UE
{
	class UVCharacterHairPiece_Hair;

	class UTESHair :
		public UTESForm
	{
	public:
		UE_DEFINE_UOBJECT(UTESHair, UTESForm, "Altar", "TESHair");

		// override
		virtual ~UTESHair();  // 00

		// members
		FString                    fullName;  // 0D8
		UVCharacterHairPiece_Hair* newMesh;   // 0E8
		std::uint8_t               flags;     // 0F0
	};
	static_assert(sizeof(UTESHair) == 0xF8);
}
