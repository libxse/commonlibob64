#pragma once

#include "RE/B/BSExtraData.h"

namespace RE
{
	class InventoryChanges;

	class __declspec(novtable) ExtraContainerChanges :
		public BSExtraData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraContainerChanges };
		inline static constexpr auto VTABLE{ VTABLE::ExtraContainerChanges };
		inline static constexpr auto TYPE{ EXTRA_DATA_TYPE::ContainerChanges };

		// members
		InventoryChanges* changes;  // 018
	};

	static_assert(sizeof(ExtraContainerChanges) == 0x20);
}
