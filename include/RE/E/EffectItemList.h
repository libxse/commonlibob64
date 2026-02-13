#pragma once

#include "RE/B/BSTList.h"
#include "RE/S/SkillLevel.h"

namespace RE
{
	class Actor;
	class EffectItem;

	class EffectItemList
	{
	public:
		// add
		virtual float             GetCost(Actor* a_actor);  // 00
		virtual std::int32_t      GetMaxEffectCount();      // 01
		virtual SkillLevel::Value GetLevel();               // 02

		// members
		BSSimpleList<EffectItem*> effectList;    // 08
		std::int32_t              hostileCount;  // 18
	};
	static_assert(sizeof(EffectItemList) == 0x20);
}
