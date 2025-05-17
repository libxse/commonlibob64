#pragma once

namespace UE
{
	class FWorldMapData
	{
	public:
		// members
		std::int64_t usableWidth;   // 000
		std::int64_t usableHeight;  // 008
		std::int32_t nwCellX;       // 010
		std::int32_t nwCellY;       // 014
		std::int32_t seCellX;       // 018
		std::int32_t seCellY;       // 01C
	};
	static_assert(sizeof(FWorldMapData) == 0x20);
}
