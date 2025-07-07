#pragma once

#include "RE/B/BaseExtraList.h"

namespace RE
{
	class ExtraDataList :
		public BaseExtraList
	{
	public:
		inline static constexpr auto RTTI = RTTI::ExtraDataList;
		inline static constexpr auto VTABLE = VTABLE::ExtraDataList;

		// override
		virtual ~ExtraDataList() override;  // 000
	};
	static_assert(sizeof(ExtraDataList) == 0x20);
}
