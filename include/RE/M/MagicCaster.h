#pragma once

#include "RE/M/MagicItem.h"

namespace RE
{
	class ActiveEffect;
	class EffectItem;
	class MagicLight;
	class MagicProjectile;
	class MagicTarget;
	class NiNode;
	class TESBoundObject;

	class MagicCaster
	{
	public:
		inline static constexpr auto RTTI = RTTI::MagicCaster;
		inline static constexpr auto VTABLE = VTABLE::MagicCaster;

		enum class State : std::int32_t;

		// add
		virtual bool           CastSpell(MagicItem* a_spell, MagicTarget* a_desiredTarget, bool a_loadCast);                                          // 00
		virtual void           CastAbility(SpellItem* a_spell, bool a_loadCast);                                                                      // 01
		virtual void           TransferDisease(SpellItem*, MagicTarget* a_desiredTarget, bool a_loadCast);                                            // 02
		virtual void           CastWornEnchantment(MagicItem* a_spell, TESBoundObject* a_source, bool a_loadCast);                                    // 03
		virtual MagicTarget*   GetTouchTarget();                                                                                                      // 04
		virtual void           StartAim();                                                                                                            // 05
		virtual void           StartCast();                                                                                                           // 06
		virtual void           SpellCast(MagicItem* a_spellCast, bool a_success);                                                                     // 07
		virtual bool           CheckCast(MagicItem* a_spell, float* a_effectStrength, MagicItem::CannotCastReason* a_reason, bool a_useBaseMagicka);  // 08
		virtual TESObjectREFR* GetCasterStatsObject();                                                                                                // 09
		virtual NiNode*        GetMagicNode();                                                                                                        // 0A
		virtual bool           TargetSelf(ActiveEffect* a_activeEffect);                                                                              // 0B
		virtual float          GetMagicEffectivenessModifier(bool a_justArmor, float a_useThisFatigue);                                               // 0C
		virtual MagicItem*     GetCurrentSpell();                                                                                                     // 0D
		virtual void           SetCurrentSpell(MagicItem* a_currentSpell);                                                                            // 0E
		virtual MagicTarget*   GetDesiredTarget();                                                                                                    // 0F
		virtual void           SetDesiredTarget(MagicTarget* a_desiredTarget);                                                                        // 10
		virtual ActiveEffect*  CreateActiveEffect(MagicItem* a_spell, EffectItem* a_effectItem, TESBoundObject* a_source);                            // 11

		// members
		MagicLight*      light;           // 008
		State            state;           // 010
		MagicProjectile* usedProjectile;  // 018
		std::byte        unk020[8];       // 020 - new
		std::byte        unk028[8];       // 028 - new
	};
	static_assert(sizeof(MagicCaster) == 0x30);
}
