#pragma once

namespace UE
{
	class FWaterShaderData
	{
	public:
		// members
		float        windVelocity;          // 000
		float        windDirection;         // 004
		float        waveAmplitude;         // 008
		float        waveFrequency;         // 00C
		float        sunPower;              // 010
		float        reflectionAmount;      // 014
		float        fresnelAmount;         // 018
		float        scrollSpeedX;          // 01C
		float        scrollSpeedY;          // 020
		float        fogDistNear;           // 024
		float        fogDistFar;            // 028
		std::int64_t shallowWaterColor;     // 02C
		std::int64_t deepWaterColor;        // 038
		std::int64_t reflectionWaterColor;  // 040
		bool         blend;                 // 048
		float        rainForce;             // 04C
		float        rainVelocity;          // 050
		float        rainFalloff;           // 054
		float        rainDampener;          // 058
		float        rainSize;              // 05C
		float        displacementForce;     // 060
		float        displacementVelocity;  // 064
		float        displacementFalloff;   // 068
		float        displacementDampener;  // 06C
		float        displacementSize;      // 070
	};
	static_assert(sizeof(FWaterShaderData) == 0x78);
}
