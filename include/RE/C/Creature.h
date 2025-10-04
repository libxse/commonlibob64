#pragma once

#include "RE/A/Actor.h"

namespace RE
{
	class Creature :
		public Actor
	{
	public:
		inline static constexpr auto RTTI = RTTI::Creature;
		inline static constexpr auto VTABLE = VTABLE::Creature;
		inline static constexpr auto FORMTYPE = FormType::Creature;

		// members
		bool ragdoll;  // 328
	};
	static_assert(sizeof(Creature) == 0x330);
}
