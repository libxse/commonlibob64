#pragma once

#include "RE/B/BSExtraData.h"

namespace RE
{
	class __declspec(novtable) ExtraCharge :
		public BSExtraData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraCharge };
		inline static constexpr auto VTABLE{ VTABLE::ExtraCharge };
		inline static constexpr auto TYPE{ EXTRA_DATA_TYPE::Charge };

		// override
		virtual bool Compare(BSExtraData* a_other) const override;  // 001

		// members
		float charge;  // 018
	};

	static_assert(sizeof(ExtraCharge) == 0x20);
}
