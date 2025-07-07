#pragma once

#include "RE/B/BSTList.h"

namespace RE
{
	class ExtraDataList;
	class TESBoundObject;

	class ItemChange
	{
	public:
		// members
		BSSimpleList<ExtraDataList*>* extraData;  // 000
		std::int32_t                  count;      // 008
		TESBoundObject*               object;     // 010
	};
	static_assert(sizeof(ItemChange) == 0x18);
}
