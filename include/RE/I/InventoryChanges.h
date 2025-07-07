#pragma once

#include "RE/B/BSTList.h"

namespace RE
{
	class ItemChange;
	class TESObjectREFR;

	class InventoryChanges
	{
	public:
		// members
		BSSimpleList<ItemChange*>* list;         // 000
		TESObjectREFR*             owner;        // 008
		float                      totalWeight;  // 010
		float                      wornWeight;   // 014
	};
	static_assert(sizeof(InventoryChanges) == 0x18);
}
