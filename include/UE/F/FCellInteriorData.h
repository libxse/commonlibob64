#pragma once

namespace UE
{
	class FCellInteriorData
	{
	public:
		// members
		std::int64_t ambient;          // 000
		std::int64_t directional;      // 008
		std::int64_t fog;              // 010
		float        fogNear;          // 018
		float        fogFar;           // 01C
		std::int64_t directionalXY;    // 020
		std::int64_t directionalZ;     // 028
		float        directionalFade;  // 030
		float        clipDist;         // 034
		std::int64_t interiorOffset;   // 038
	};
	static_assert(sizeof(FCellInteriorData) == 0x40);
}
