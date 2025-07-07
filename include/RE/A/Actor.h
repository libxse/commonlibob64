#pragma once

#include "RE/A/ACTION_FLAGS.h"
#include "RE/A/ACTOR_LIFE_STATE.h"
#include "RE/A/ACTOR_TYPE.h"
#include "RE/A/ActorDeathInfos.h"
#include "RE/A/ActorValue.h"
#include "RE/B/BSTList.h"
#include "RE/D/DIALOGUE_EMOTION.h"
#include "RE/M/MATERIAL_TYPE.h"
#include "RE/M/MagicCaster.h"
#include "RE/M/MagicTarget.h"
#include "RE/M/MobileObject.h"
#include "RE/M/ModifierList.h"
#include "RE/S/SKILL_ACTION.h"
#include "RE/V/VAnimationPairingComponentHandlers.h"
#include "RE/V/VPreloadAssetsHandlers.h"
#include "RE/W/WEAPON_TYPE.h"

namespace RE
{
	class ArrowProjectile;
	class CastPowerItem;
	class CombatController;
	class Crime;
	class DialogueResponse;
	class DispositionModifier;
	class FurnitureMark;
	class ItemChange;
	class OblivionCombatHitData;
	class SpectatorEvent;
	class TESObject;
	class TESPackage;
	class TESTopicInfo;
	class TrespassPackage;

	class Actor :
		public MobileObject,
		public MagicCaster,
		public MagicTarget
	{
	public:
		inline static constexpr auto RTTI = RTTI::Actor;
		inline static constexpr auto VTABLE = VTABLE::Actor;
		inline static constexpr auto FORMTYPE = FormType::ActorCharacter;

		// override (TESForm)
		virtual ~Actor() override;                                                                                                                                                                                                                                                  // 04
		virtual std::uint16_t           GetSaveSize(std::uint32_t a_changeFlags) override;                                                                                                                                                                                          // 13
		virtual void                    SaveGame(std::uint32_t a_changeFlags) override;                                                                                                                                                                                             // 14
		virtual void                    LoadGame(std::uint32_t a_flags, std::uint32_t a_currentFlags) override;                                                                                                                                                                     // 15
		virtual void                    InitLoadGame(std::uint32_t a_flags, std::uint32_t a_oldFlags) override;                                                                                                                                                                     // 16
		virtual void                    FinishInitLoadGame(std::uint32_t a_flags, std::uint32_t a_oldFlags) override;                                                                                                                                                               // 17
		virtual void                    Revert(std::uint32_t a_flags) override;                                                                                                                                                                                                     // 18
		virtual float                   VoiceSoundFunction(TESTopic* a_topic, Actor* a_target, bool a_playerHead, bool a_alwaysPlay, bool a_forceCorrectDuration) override;                                                                                                         // 3C
		virtual NiPoint3*               GetStartingAngle() override;                                                                                                                                                                                                                // 41
		virtual NiPoint3*               GetStartingLocation() override;                                                                                                                                                                                                             // 42
		virtual void                    UpdateRefLight() override;                                                                                                                                                                                                                  // 44
		virtual void                    AddBoundObjectItem(TESBoundObject* a_object, ExtraDataList* a_extra, std::int32_t a_number) override;                                                                                                                                       // 45
		virtual TESObjectREFR*          RemoveItem(TESBoundObject* a_object, ExtraDataList* a_extra, std::int32_t a_number, bool a_stealing, bool a_dropWorld, TESObjectREFR* a_containerObj, NiPoint3* a_point, NiPoint3* a_rotate, bool a_delete, bool a_preferStolen) override;  // 46
		virtual bool                    AddWornItem(TESBoundObject* a_object, std::int32_t a_number, ExtraDataList* a_extra, bool a_forceEquip) override;                                                                                                                           // 48
		virtual void                    DoTrap(TrapEntry* a_trap, TargetEntry* a_target) override;                                                                                                                                                                                  // 4A
		virtual void                    AddObjectToContainer(TESBoundObject* a_obj, ExtraDataList* a_extra, std::int32_t a_count) override;                                                                                                                                         // 4B
		virtual NiPoint3*               GetLookingAtLocation() override;                                                                                                                                                                                                            // 4D
		virtual MagicCaster*            GetMagicCaster() override;                                                                                                                                                                                                                  // 4E
		virtual MagicTarget*            GetMagicTarget() override;                                                                                                                                                                                                                  // 4F
		virtual void                    SetTemplateActorBase(TESActorBase* a_template) override;                                                                                                                                                                                    // 51
		virtual const NiPoint3*         GetLocationOnReference() override;                                                                                                                                                                                                          // 63
		virtual void                    SetActionComplete(bool a_value) override;                                                                                                                                                                                                   // 65
		virtual void                    SetMovementComplete(bool a_value) override;                                                                                                                                                                                                 // 66
		virtual void                    ResetInventory(bool a_leveledOnly) override;                                                                                                                                                                                                // 67
		virtual SIT_SLEEP_STATE         GetSitSleepState() override;                                                                                                                                                                                                                // 69
		virtual bool                    IsDead(bool a_notEssential) override;                                                                                                                                                                                                       // 6C
		virtual bool                    IsKnockedOut() override;                                                                                                                                                                                                                    // 6D
		virtual bool                    IsParalyzed() override;                                                                                                                                                                                                                     // 6E
		virtual bool                    MoveToHigh() override;                                                                                                                                                                                                                      // 78
		virtual bool                    MoveToLow() override;                                                                                                                                                                                                                       // 79
		virtual bool                    MoveToMiddleLow() override;                                                                                                                                                                                                                 // 7A
		virtual bool                    MoveToMiddleHigh() override;                                                                                                                                                                                                                // 7B
		virtual bhkCharacterController* Move(float a_deltaTime, NiPoint3& a_deltaMove, std::uint32_t a_moveDir) override;                                                                                                                                                           // 7C
		virtual bhkCharacterController* Jump() override;                                                                                                                                                                                                                            // 7D
		virtual void                    Process(float a_delta) override;                                                                                                                                                                                                            // 7F
		virtual bool                    ChangeProcessLevel() override;                                                                                                                                                                                                              // 80
		virtual void                    EvaluateDetection(float a_number) override;                                                                                                                                                                                                 // 84
		virtual float                   GetDetectionTimer() override;                                                                                                                                                                                                               // 85
		virtual void                    ReduceDetectionTimer() override;                                                                                                                                                                                                            // 86
		virtual void                    SetHeading(TESObjectREFR* a_targetReference) override;                                                                                                                                                                                      // 88
		virtual void                    SetHeading(float a_angle) override;                                                                                                                                                                                                         // 89
		virtual bool                    GetRunsInLow() override;                                                                                                                                                                                                                    // 8B
		virtual float                   GetAcrobatics() override;                                                                                                                                                                                                                   // 8C
		virtual bool                    IsDying() override;                                                                                                                                                                                                                         // 8D

		// override (IVPairableItem)
		virtual void OnPostPairItem() override;    // 04
		virtual void OnPreUnpairItem() override;   // 05
		virtual void OnPostUnpairItem() override;  // 06

		// override (MagicCaster)
		virtual bool           CastSpell(MagicItem* a_spell, MagicTarget* a_desiredTarget, bool a_loadCast) override;                                          // 00
		virtual void           CastAbility(SpellItem* a_spell, bool a_loadCast) override;                                                                      // 01
		virtual void           TransferDisease(SpellItem*, MagicTarget* a_desiredTarget, bool a_loadCast) override;                                            // 02
		virtual void           StartCast() override;                                                                                                           // 06
		virtual void           SpellCast(MagicItem* a_spellCast, bool a_success) override;                                                                     // 07
		virtual bool           CheckCast(MagicItem* a_spell, float* a_effectStrength, MagicItem::CannotCastReason* a_reason, bool a_useBaseMagicka) override;  // 08
		virtual TESObjectREFR* GetCasterStatsObject() override;                                                                                                // 09
		virtual NiNode*        GetMagicNode() override;                                                                                                        // 0A
		virtual MagicItem*     GetCurrentSpell() override;                                                                                                     // 0D
		virtual void           SetCurrentSpell(MagicItem* a_currentSpell) override;                                                                            // 0E
		virtual MagicTarget*   GetDesiredTarget() override;                                                                                                    // 0F
		virtual void           SetDesiredTarget(MagicTarget* a_desiredTarget) override;                                                                        // 10

		// override (MagicTarget)
		virtual bool                         AddTarget(MagicCaster* a_caster, MagicItem* a_spell, ActiveEffect* a_activeEffect, bool a_areaTarget) override;       // 00
		virtual TESObjectREFR*               GetTargetStatsObject() override;                                                                                      // 01
		virtual BSSimpleList<ActiveEffect*>* GetActiveEffectList() override;                                                                                       // 02                                                                            // 03
		virtual void                         EffectAdded(ActiveEffect* a_effect) override;                                                                         // 04
		virtual void                         EffectRemoved(ActiveEffect* a_effect) override;                                                                       // 05
		virtual void                         EffectReflected(MagicCaster* a_caster, ActiveEffect* a_effect) override;                                              // 06
		virtual void                         EffectAbsorbed(MagicCaster* a_caster, ActiveEffect* a_effect) override;                                               // 07
		virtual float                        CheckResistance(MagicCaster* a_caster, MagicItem* a_spell, ActiveEffect* a_activeEffect) override;                    // 08
		virtual bool                         CheckAbsorb(MagicCaster* a_caster, MagicItem* a_spell, ActiveEffect* a_activeEffect, bool a_reducedChance) override;  // 09
		virtual bool                         CheckReflect(MagicCaster* a_caster, MagicItem* a_spell, ActiveEffect* a_activeEffect) override;                       // 0A

		// add
		virtual std::int32_t           GetFame();                                                                                                                                                                                             // 090
		virtual std::int32_t           GetInfamy();                                                                                                                                                                                           // 091
		virtual void                   Resurrect(bool a_resetInventory, bool a_attach3D, bool a_getUp);                                                                                                                                       // 092
		virtual void                   SetAdvanceNumber(std::int32_t a_number);                                                                                                                                                               // 093
		virtual std::int32_t           GetAdvanceNumber();                                                                                                                                                                                    // 094
		virtual void                   SetSkillAdvanceDelayed(ActorValue::Index a_skill);                                                                                                                                                     // 095
		virtual ActorValue::Index      GetSkillAdvanceDelayed();                                                                                                                                                                              // 096
		virtual bool                   DoDamage(float a_healthDamage, float a_fatigueDamage, Actor* a_source);                                                                                                                                // 097
		virtual std::int32_t           GetDisposition(Actor* a_targetActor);                                                                                                                                                                  // 098
		virtual void                   Update(float a_delta);                                                                                                                                                                                 // 099
		virtual void                   InitiateMountHorsePackage(Creature* a_horse);                                                                                                                                                          // 09A
		virtual void                   InitiateDismountHorsePackage();                                                                                                                                                                        // 09B
		virtual void                   SetDialogueWithPlayer(bool a_value);                                                                                                                                                                   // 09C
		virtual void                   StealAlarm(TESObjectREFR* a_ref, TESBoundObject* a_obj, std::int32_t a_num, std::int32_t a_total, TESForm* a_owner);                                                                                   // 09D
		virtual void                   PickpocketAlarm(TESObjectREFR* a_ref, TESBoundObject* a_obj, std::int32_t a_num);                                                                                                                      // 09E
		virtual void                   AttackAlarm(TESObjectREFR* a_ref, bool a_modDisposition);                                                                                                                                              // 09F
		virtual void                   MurderAlarm(TESObjectREFR* a_ref);                                                                                                                                                                     // 0A0
		virtual std::int32_t           TrespassAlarm(TESObjectREFR* a_ref, TESForm* a_owner, std::int32_t a_crime);                                                                                                                           // 0A1
		virtual void                   StealHorseAlarm(TESObjectREFR* a_ref);                                                                                                                                                                 // 0A2
		virtual float                  GetCrimeGold();                                                                                                                                                                                        // 0A3
		virtual void                   ModCrimeGold(float a_amount);                                                                                                                                                                          // 0A4
		virtual float                  GetTurningSpeed();                                                                                                                                                                                     // 0A5
		virtual bool                   IsOverEncumbered();                                                                                                                                                                                    // 0A6
		virtual bool                   GetVampireFed();                                                                                                                                                                                       // 0A7
		virtual void                   SetVampireFed(bool a_value);                                                                                                                                                                           // 0A8
		virtual BirthSign*             GetBirthSign();                                                                                                                                                                                        // 0A9
		virtual float                  GetReach();                                                                                                                                                                                            // 0AA
		virtual void                   SetRefraction(bool a_enable, float a_refractionPower);                                                                                                                                                 // 0AB
		virtual void                   SetRagDoll(bool a_found);                                                                                                                                                                              // 0AC
		virtual bool                   HasRagDoll();                                                                                                                                                                                          // 0AD
		virtual ACTOR_TYPE             GetActorType();                                                                                                                                                                                        // 0AE
		virtual TESSkill*              GetHighestSkill();                                                                                                                                                                                     // 0AF
		virtual std::int32_t           GetActorValue(ActorValue::Index a_index);                                                                                                                                                              // 0B0
		virtual float                  GetActorFloatValue(ActorValue::Index a_index);                                                                                                                                                         // 0B1
		virtual void                   SetActorValue(ActorValue::Index a_index, float a_value);                                                                                                                                               // 0B2
		virtual void                   SetActorValue(ActorValue::Index a_index, std::int32_t a_value);                                                                                                                                        // 0B3
		virtual void                   MagicModActorValue(ActorValue::Index a_index, float a_value, Actor* a_attacker);                                                                                                                       // 0B4
		virtual void                   MagicModActorValue(ActorValue::Index a_index, std::int32_t a_value, Actor* a_attacker);                                                                                                                // 0B5
		virtual void                   ScriptModActorValue(ActorValue::Index a_index, float a_value, Actor* a_attacker);                                                                                                                      // 0B6
		virtual void                   ScriptModActorValue(ActorValue::Index a_index, std::int32_t a_value, Actor* a_attacker);                                                                                                               // 0B7
		virtual void                   GameModActorValue(ActorValue::Index a_index, float a_value, Actor* a_attacker, bool a_canStopNaturalRegen);                                                                                            // 0B8
		virtual void                   GameModActorValue(ActorValue::Index a_index, std::int32_t a_value, Actor* a_attacker, bool a_canStopNaturalRegen);                                                                                     // 0B9
		virtual void                   ModActorBaseValue(ActorValue::Index a_index, float a_value);                                                                                                                                           // 0BA
		virtual void                   ModActorBaseValue(ActorValue::Index a_index, std::int32_t a_value);                                                                                                                                    // 0BB
		virtual void                   PayFine();                                                                                                                                                                                             // 0BC
		virtual bool                   RemoveWornItem(TESBoundObject* a_obj, std::int32_t a_num, ExtraDataList* a_extra, bool a_left, bool a_force);                                                                                          // 0BD
		virtual ItemChange*            GetBestWeapon(WEAPON_TYPE a_type);                                                                                                                                                                     // 0BE
		virtual ItemChange*            GetBestAmmo();                                                                                                                                                                                         // 0BF
		virtual void                   ResetArmorRating();                                                                                                                                                                                    // 0C0
		virtual bool                   DamageEquipment(ItemChange* a_equipment, float a_damage, bool a_ignoreArmorSkill);                                                                                                                     // 0C1
		virtual TESObjectREFR*         DropObject(TESObject* a_obj, ExtraDataList* a_extra, std::int32_t a_number, NiPoint3* a_point, NiPoint3* a_rotate);                                                                                    // 0C2
		virtual void                   PickUpObject(TESObjectREFR* a_obj, std::int32_t a_count, bool a_flag);                                                                                                                                 // 0C3
		virtual void                   CastScroll(TESObjectBOOK* a_scroll, MagicTarget* a_target);                                                                                                                                            // 0C4
		virtual bool                   CheckCastWhenStrikesEnchantment(ItemChange* a_weapon, Actor* a_target, ArrowProjectile* a_arrow, bool* a_insufficientCharge);                                                                          // 0C5
		virtual void                   UpdateWornEnchantments(float a_value);                                                                                                                                                                 // 0C6
		virtual void                   CheckStaffEnchantment(ItemChange* a_staff);                                                                                                                                                            // 0C7
		virtual bool                   AddSpell(SpellItem* a_spell);                                                                                                                                                                          // 0C8
		virtual bool                   RemoveSpell(SpellItem* a_spell);                                                                                                                                                                       // 0C9
		virtual void                   StartCast_Altar();                                                                                                                                                                                     // 0CA
		virtual void                   UpdateMagic(float a_elapsedTime);                                                                                                                                                                      // 0CB
		virtual void                   UseAmmo();                                                                                                                                                                                             // 0CC
		virtual void                   CleanOrphanedMagicModifiers();                                                                                                                                                                         // 0CD
		virtual bool                   IsInCombatWithGuard();                                                                                                                                                                                 // 0CE
		virtual bool                   InitiateDialogue(Actor* a_target, bool a_flag, TESTopic* a_topic);                                                                                                                                     // 0CF
		virtual void                   InitiateDeadReaction(Actor* a_target);                                                                                                                                                                 // 0D0
		virtual void                   InitiateTrespassPackage(TrespassPackage* a_package);                                                                                                                                                   // 0D1
		virtual void                   InitiateVampireFeedPackage(Actor* a_target, TESObjectREFR* a_furniture, FurnitureMark* a_marker, std::uint8_t a_index);                                                                                // 0D2
		virtual void                   UpdateActorInDialogue(float a_delta, DialogueResponse* a_response, std::uint32_t a_overrideEmotion, TESTopicInfo* a_topicInfo);                                                                        // 0D3
		virtual void                   CombatVocalization(Actor* a_target, std::int32_t a_dialogueTopic, bool a_interrupt);                                                                                                                   // 0D4
		virtual void                   EndDialogue();                                                                                                                                                                                         // 0D5
		virtual void                   InitiateAlarm(Crime* a_crime, std::int32_t a_procedureIndex, bool a_sendAlarm, Actor* a_actor);                                                                                                        // 0D6
		virtual void                   InitiateSpectator(SpectatorEvent* a_event);                                                                                                                                                            // 0D7
		virtual void                   InitiateFlee(Actor* a_actor, bool a_runOnce, bool a_knows, TESObjectCELL* a_cell, TESObjectREFR* a_ref);                                                                                               // 0D8
		virtual void                   InitiateSearchForAttacker(Actor* a_attacker);                                                                                                                                                          // 0D9
		virtual void                   InitiateGetUpPackage();                                                                                                                                                                                // 0DA
		virtual void                   SetAlpha(float a_value);                                                                                                                                                                               // 0DB
		virtual float                  GetAlpha();                                                                                                                                                                                            // 0DC
		virtual void                   StartCombat(Actor* a_target, bool a_forceCombat, bool a_isAggressor, bool a_fleeing, std::int32_t a_priority, bool a_castSpell);                                                                       // 0DD
		virtual CombatController*      GetCombatController();                                                                                                                                                                                 // 0DE
		virtual bool                   IsInCombat(bool a_sittingCheck);                                                                                                                                                                       // 0DF
		virtual Actor*                 GetCombatTarget();                                                                                                                                                                                     // 0E0
		virtual void                   UpdateCombat(float a_elapsedTime);                                                                                                                                                                     // 0E1
		virtual void                   StopCombat(Actor* a_attacker);                                                                                                                                                                         // 0E2
		virtual void                   PerformOneRoundofCombat();                                                                                                                                                                             // 0E3
		virtual float                  GetArmorRating();                                                                                                                                                                                      // 0E4
		virtual std::int32_t           GetAttackDamage();                                                                                                                                                                                     // 0E5
		virtual bool                   IsYielding();                                                                                                                                                                                          // 0E6
		virtual bool                   IsTrespassing();                                                                                                                                                                                       // 0E7
		virtual bool                   IsFeeding();                                                                                                                                                                                           // 0E8
		virtual bool                   IsProcessingTrespassAlarm();                                                                                                                                                                           // 0E9
		virtual bool                   GetUsesAttackPercents();                                                                                                                                                                               // 0EA
		virtual void                   UpdateTimedSystems(float a_clockTime);                                                                                                                                                                 // 0EB
		virtual void                   OpponentYields(Actor* a_opponent);                                                                                                                                                                     // 0EC
		virtual bool                   WouldAcceptYield(Actor* a_opponent);                                                                                                                                                                   // 0ED
		virtual void                   ModifyDispositionTowardActor(Actor* a_actor, float a_amount);                                                                                                                                          // 0EE
		virtual float                  GetDispositionModifierTowardActor(Actor* a_actor);                                                                                                                                                     // 0EF
		virtual void                   SetStartingPosition();                                                                                                                                                                                 // 0F0
		virtual Creature*              GetHorse();                                                                                                                                                                                            // 0F1
		virtual void                   SetHorse(Creature* a_horse);                                                                                                                                                                           // 0F2
		virtual Character*             GetRider();                                                                                                                                                                                            // 0F3
		virtual void                   SetRider(Character* a_rider);                                                                                                                                                                          // 0F4
		virtual bool                   HasBeenAttacked();                                                                                                                                                                                     // 0F5
		virtual void                   SetBeenAttacked(bool a_value);                                                                                                                                                                         // 0F6
		virtual void                   HitMe(Actor* a_attacker, float a_damage, float a_blocked, const NiPoint3& a_startPos, const NiPoint3& a_stopPos);                                                                                      // 0F7
		virtual void                   UseSkill(ActorValue::Index a_index, SKILL_ACTION a_action, float a_modifier);                                                                                                                          // 0F8
		virtual void                   UseSkill(ActorValue::Index a_index, float a_usage, TESSkill* a_skill);                                                                                                                                 // 0F9
		virtual void                   UseSkillWithSpellCost(ActorValue::Index a_index, float a_spellCost);                                                                                                                                   // 0FA
		virtual void                   AnimationPairing();                                                                                                                                                                                    // 0FB
		virtual void                   PairingGateSendAnimationTransitionOnStateChange();                                                                                                                                                     // 0FC
		virtual void                   SpecialDynamicIdleAnimationPairing();                                                                                                                                                                  // 0FD
		virtual void                   SendDynamicIdleAnimationChange(TESFormID a_formID);                                                                                                                                                    // 0FE
		virtual void                   GroundMaterialPairing(MATERIAL_TYPE a_groundMaterialType);                                                                                                                                             // 0FF
		virtual void                   SoundEffectPairing(const char* a_formEditorID, const char* a_handlerLabel, bool a_useLocation, float a_x, float a_y, float a_z);                                                                       // 100
		virtual void                   DialoguePairing(TESFormID a_topicInfoFormID, TESFormID a_topicInfoResponseFormID, bool a_isSpatialized, bool a_force, const char* a_voiceFilePath, std::int32_t a_combatVocalizationType);             // 101
		virtual void                   VoiceSoundPairing(const char* a_formEditorID, const char* a_handlerLabel);                                                                                                                             // 102
		virtual void                   SendVoiceFactionsToAltar();                                                                                                                                                                            // 103
		virtual void                   LogMissingDialogue(const char* a_soundAssetPath, const char* a_speakerDebugName, bool a_missingInBSA);                                                                                                 // 104
		virtual void                   DoPreloadPairedActor(VPreloadAssetsHandlers::PRELOAD_PRIORITY a_basePriority, VPreloadAssetsHandlers::PRELOAD_PRIORITY a_higherPriority);                                                              // 105
		virtual void                   DoPreloadPairedActorAndInventoryItems(VPreloadAssetsHandlers::PRELOAD_PRIORITY a_basePriority, VPreloadAssetsHandlers::PRELOAD_PRIORITY a_higherPriority);                                             // 106
		virtual void                   DoReleasePairedActorAndInventoryItems();                                                                                                                                                               // 107
		virtual void                   DoPreloadEarlyUnpairedActor(VPreloadAssetsHandlers::PRELOAD_PRIORITY a_basePriority, VPreloadAssetsHandlers::PRELOAD_PRIORITY a_higherPriority, float a_distanceFromPlayerInMeters);                   // 108
		virtual void                   DoPreloadEarlyUnpairedActorAndInventoryItems(VPreloadAssetsHandlers::PRELOAD_PRIORITY a_basePriority, VPreloadAssetsHandlers::PRELOAD_PRIORITY a_higherPriority, float a_distanceFromPlayerInMeters);  // 109
		virtual void                   DoReleaseCachedAssetsForUnpairedActorAndInventoryItems();                                                                                                                                              // 10A
		virtual void                   StartAnimOn1stPerson(std::uint16_t a_animGroup, ACTION_FLAGS a_flags);                                                                                                                                 // 10B
		virtual void                   AttackedBy(Actor* a_attacker, ActiveEffect* a_hostileEffect);                                                                                                                                          // 10C
		virtual OblivionCombatHitData* CombatHit_Altar(bool a_powerAttack, ArrowProjectile* a_arrow, Actor* a_target, ActorValue::Index a_weaponAttribute, float a_sneakDamageMult, bool a_shieldBash);                                       // 10D
		virtual void                   CombatHit(bool a_powerAttack, ArrowProjectile* a_arrow, Actor* a_target, ActorValue::Index a_weaponAttribute, float a_sneakDamageMult, bool a_shieldBash);                                             // 10E
		virtual void                   NonCombatHit(bool a_powerAttack, ArrowProjectile* a_arrow, Actor* a_target);                                                                                                                           // 10F
		virtual void                   HandleBlockedAttack(float a_fullDamage, float a_percentageBlocked, Actor* a_blockingActor, ArrowProjectile* a_arrow);                                                                                  // 110
		virtual void                   HandleHealthDamage(Actor* a_attacker, float a_damage);                                                                                                                                                 // 111

		void         EquipObject(TESBoundObject* a_object, std::int32_t a_count, ExtraDataList* a_extra, bool a_now = false, bool a_force = false);
		std::int32_t GetItemCountInContainer(TESBoundObject* a_object) const;
		std::int16_t GetLevel() const;
		bool         UnequipObject(TESBoundObject* a_object, std::int32_t a_count, ExtraDataList* a_extra, bool a_force = false, bool a_equipCalling = true);

		// members
		ActorDeathInfos                                       actorKilledInfos;                // 178
		bool                                                  isWalkingOnWater;                // 1D0
		bool                                                  wasKilledByPlayer;               // 1D1
		DIALOGUE_EMOTION                                      persuasionEmotion;               // 1D4
		float                                                 emotionValue;                    // 1D8
		bool                                                  processMe;                       // 1DC
		Actor*                                                myKiller;                        // 1E0
		bool                                                  murderAlarm;                     // 1E8
		float                                                 checkMyDeadBodyTimer;            // 1EC
		ModifierList                                          scriptModifiers;                 // 1F0
		bool                                                  useAltVoice;                     // 218
		bool                                                  useBeggarVoice;                  // 219
		bool                                                  isMoveModeFromReverse;           // 21A
		bool                                                  wantsToYield;                    // 21B
		BSSimpleList<CastPowerItem*>                          castPowers;                      // 220
		BSSimpleList<DispositionModifier*>                    dispModifierList;                // 230
		float                                                 targetPriorityTimer;             // 240
		ACTOR_LIFE_STATE                                      lifeState;                       // 244
		BSSimpleList<TESPackage*>                             donePackageList;                 // 248
		float                                                 lastUpdate;                      // 258
		bool                                                  deadFlag;                        // 25C
		std::int32_t                                          visFlags;                        // 260
		bool                                                  forceRun;                        // 264
		bool                                                  forceSneak;                      // 265
		bool                                                  forceUpdateQuestTarget;          // 266
		TESObjectREFR*                                        addMovementBlocked;              // 268
		TESActorBase*                                         templateActorBase;               // 270
		Actor*                                                horseRider;                      // 278
		bool                                                  inWater;                         // 280
		bool                                                  isInLowFatigueState;             // 281
		bool                                                  hasEnteredWaterSurface;          // 282
		bool                                                  hasEnteredUnderWater;            // 283
		float                                                 headTrackTimer;                  // 284
		bool                                                  wasInFrustum;                    // 288
		Actor*                                                dialogueItemTarget;              // 290
		NiPoint3                                              editorLocCoord;                  // 298
		float                                                 editorLocZRot;                   // 2A4
		TESForm*                                              editorLocForm;                   // 2A8
		bool                                                  setOnDeath;                      // 2B0
		bool                                                  containerReset;                  // 2B1
		bool                                                  hasTakenFallDamage;              // 2B2
		float                                                 naturalHealthRegenPeriod;        // 2B4
		float                                                 naturalMagickaRegenPeriod;       // 2B8
		float                                                 naturalFatigueRegenPeriod;       // 2BC
		MATERIAL_TYPE                                         lastGroundMaterial;              // 2C0
		std::uint32_t                                         lastSpecialIdleFormId;           // 2C4
		std::uint32_t                                         lastDynamicIdleFormId;           // 2C8
		bool                                                  isSpecialIdleChanged;            // 2CC
		std::uint16_t                                         lastDynamicIdleAnimGroup;        // 2CE
		bool                                                  isInDynamicIdle;                 // 2D0
		VAnimationPairingComponentHandlers::OblivionAnimState lastAnimState;                   // 2D4
		bool                                                  isHoldingABow;                   // 304
		bool                                                  fatigueRestorationEnabled;       // 305
		float                                                 permanentFatigueDrainPerSecond;  // 308
		bool                                                  isFatigueFreezeActive;           // 30C
		float                                                 updateTargetTimer;               // 310
	};
	static_assert(sizeof(Actor) == 0x318);
}

namespace RE
{
	inline void Actor::EquipObject(TESBoundObject* a_object, std::int32_t a_count, ExtraDataList* a_extra, bool a_now, bool a_force)
	{
		using func_t = decltype(&Actor::EquipObject);
		static REL::Relocation<func_t> func{ ID::Actor::EquipObject };
		func(this, a_object, a_count, a_extra, a_now, a_force);
	}

	inline std::int32_t Actor::GetItemCountInContainer(TESBoundObject* a_object) const
	{
		using func_t = decltype(&Actor::GetItemCountInContainer);
		static REL::Relocation<func_t> func{ ID::Actor::GetItemCountInContainer };
		return func(this, a_object);
	}

	inline std::int16_t Actor::GetLevel() const
	{
		using func_t = decltype(&Actor::GetLevel);
		static REL::Relocation<func_t> func{ ID::Actor::GetLevel };
		return func(this);
	}

	inline bool Actor::UnequipObject(TESBoundObject* a_object, std::int32_t a_count, ExtraDataList* a_extra, bool a_force, bool a_equipCalling)
	{
		using func_t = bool (Actor::*)(TESBoundObject*, std::int32_t, ExtraDataList*, bool, bool, bool);
		static REL::Relocation<func_t> func{ ID::Actor::UnequipObject };
		return func(this, a_object, a_count, a_extra, false, a_force, a_equipCalling);
	}
}
