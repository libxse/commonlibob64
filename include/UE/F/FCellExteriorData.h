#pragma once

namespace UE
{
	class FCellExteriorData
	{
	public:
		// members
		std::int32_t cellX;  // 000
		std::int32_t cellY;  // 004
	};
	static_assert(sizeof(FCellExteriorData) == 0x8);
}
