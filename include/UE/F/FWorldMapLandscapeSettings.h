#pragma once

namespace UE
{
	class FWorldMapLandscapeSettings
	{
	public:
		// members
		float        tesToUnrealWorldScaleFactor;  // 000
		float        tesCellMetricSize;            // 004
		float        tesCellQuadsCount;            // 008
		float        tesCellQuadMetricSize;        // 00C
		std::int32_t tesCellsPerComponent;         // 010
		std::int32_t sectionsPerComponent;         // 014
		std::int32_t quadsPerSection;              // 018
		std::int32_t worldPartitionGridSize;       // 01C
		bool         flipYAxis;                    // 020
		bool         generateLayers;               // 021
		bool         debugCells;                   // 022
	};
	static_assert(sizeof(FWorldMapLandscapeSettings) == 0x24);
}
