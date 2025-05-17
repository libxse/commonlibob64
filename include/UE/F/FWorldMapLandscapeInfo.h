#pragma once

#include "UE/F/FIntPoint.h"
#include "UE/F/FVector2.h"

namespace UE
{
	class FWorldMapLandscapeInfo
	{
	public:
		// members
		FInt32Point tesWorldspaceCellsCount;   // 000
		FInt32Point tesWorldspaceQuadsCount;   // 008
		FVector2d   tesWorldspaceMetricSize;   // 010
		FInt32Point landscapeComponentsCount;  // 020
		FInt32Point landscapeSectionsCount;    // 028
		FInt32Point landscapeQuadsCount;       // 030
		FVector2d   landscapeMetricSize;       // 038
		FVector2d   landscapeQuadMetricSize;   // 048
		float       minLandscapeMetricHeight;  // 058
		float       maxLandscapeMetricHeight;  // 05C
	};
	static_assert(sizeof(FWorldMapLandscapeInfo) == 0x60);
}
