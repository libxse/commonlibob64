#pragma once

#include "UE/F/FWaterShaderData.h"
#include "UE/U/UTESForm.h"

namespace UE
{
	class UTexture2D;

	class UTESWaterForm :
		public UTESForm
	{
	public:
		UE_DEFINE_UOBJECT(UTESWaterForm, UTESForm, "Altar", "TESWaterForm");

		// override
		virtual ~UTESWaterForm();

		// members
		TSoftObjectPtr<UTexture2D> texture;     // 0D8
		std::int32_t               alpha;       // 100
		std::int32_t               flags;       // 104
		FWaterShaderData           waterData;   // 108
		FString                    materialID;  // 180
	};
	static_assert(sizeof(UTESWaterForm) == 0x190);
}
