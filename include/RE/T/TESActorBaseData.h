#pragma once
#include "RE/A/ACTOR_BASE_DATA.h"
#include "RE/B/BSTList.h"
#include "RE/B/BaseFormComponent.h"
namespace RE
{
	class FACTION_RANK;
	class TESLevItem;
	struct TESActorBaseData :
		public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI::TESActorBaseData;
		inline static constexpr auto VTABLE = VTABLE::TESActorBaseData;

		[[nodiscard]] bool IsEssential() const noexcept;
		void               SetEssential(bool a_value) noexcept;

		// members
		ACTOR_BASE_DATA             actorData;  // 08
		TESLevItem*                 deathItem;  // 18
		BSSimpleList<FACTION_RANK*> factions;   // 20
	};
	static_assert(sizeof(TESActorBaseData) == 0x30);

	inline bool TESActorBaseData::IsEssential() const noexcept
	{
		return actorData.actorBaseFlags.any(ACTOR_BASE_DATA::Flags::Essential);
	}

	inline void TESActorBaseData::SetEssential(bool a_value) noexcept
	{
		if (a_value) {
			actorData.actorBaseFlags.set(ACTOR_BASE_DATA::Flags::Essential);
		} else {
			actorData.actorBaseFlags.reset(ACTOR_BASE_DATA::Flags::Essential);
		}
	}
}
