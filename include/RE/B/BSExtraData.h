#pragma once

#include "RE/E/EXTRA_DATA_TYPE.h"

namespace RE
{
	class __declspec(novtable) BSExtraData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSExtraData };
		inline static constexpr auto VTABLE{ VTABLE::BSExtraData };
		inline static constexpr auto TYPE{ EXTRA_DATA_TYPE::None };

		// add
		virtual ~BSExtraData() = default;                  // 000
		virtual bool Compare(BSExtraData* a_other) const;  // 001

		// members
		REX::Enum<EXTRA_DATA_TYPE, std::uint8_t> type;  // 008
		BSExtraData*                             next;  // 010
	};
	static_assert(sizeof(BSExtraData) == 0x18);
}
