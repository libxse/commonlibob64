#pragma once

#include "RE/A/Actor.h"

namespace RE
{
	class BipedAnim;

	class Character :
		public Actor
	{
	public:
		inline static constexpr auto RTTI = RTTI::Character;
		inline static constexpr auto VTABLE = VTABLE::Character;
		inline static constexpr auto FORMTYPE = FormType::ActorCharacter;

		// override (TESForm)
		virtual ~Character() override;                                                                                                                                                                                                        // 004
		virtual std::uint16_t GetSaveSize(std::uint32_t a_changeFlags) override;                                                                                                                                                              // 013
		virtual void          SaveGame(std::uint32_t a_changeFlags) override;                                                                                                                                                                 // 014
		virtual void          LoadGame(std::uint32_t a_flags, std::uint32_t a_currentFlags) override;                                                                                                                                         // 015
		virtual void          InitLoadGame(std::uint32_t a_flags, std::uint32_t a_oldFlags) override;                                                                                                                                         // 016
		virtual void          FinishInitLoadGame(std::uint32_t a_flags, std::uint32_t a_oldFlags) override;                                                                                                                                   // 017
		virtual void          Revert(std::uint32_t a_flags) override;                                                                                                                                                                         // 018
		virtual float         GetScale() override;                                                                                                                                                                                            // 040
		virtual bool          AddWornItem(TESBoundObject* a_object, std::int32_t a_number, ExtraDataList* a_extra, bool a_forceEquip) override;                                                                                               // 048
		virtual void          Set3D(NiAVObject* a_node) override;                                                                                                                                                                             // 05A
		virtual NiAVObject*   Get3D() override;                                                                                                                                                                                               // 05B
		virtual BipedAnim*    GetBiped() override;                                                                                                                                                                                            // 060
		virtual void          SetBiped(BipedAnim* a_biped) override;                                                                                                                                                                          // 061
		virtual void          InitiateMountHorsePackage(Creature* a_horse) override;                                                                                                                                                          // 09A
		virtual void          InitiateDismountHorsePackage() override;                                                                                                                                                                        // 09B
		virtual void          StealAlarm(TESObjectREFR* a_ref, TESBoundObject* a_obj, std::int32_t a_num, std::int32_t a_total, TESForm* a_owner) override;                                                                                   // 09D
		virtual void          PickpocketAlarm(TESObjectREFR* a_ref, TESBoundObject* a_obj, std::int32_t a_num) override;                                                                                                                      // 09E
		virtual void          AttackAlarm(TESObjectREFR* a_ref, bool a_modDisposition) override;                                                                                                                                              // 09F
		virtual void          MurderAlarm(TESObjectREFR* a_ref) override;                                                                                                                                                                     // 0A0
		virtual std::int32_t  TrespassAlarm(TESObjectREFR* a_ref, TESForm* a_owner, std::int32_t a_crime) override;                                                                                                                           // 0A1
		virtual void          StealHorseAlarm(TESObjectREFR* a_ref) override;                                                                                                                                                                 // 0A2
		virtual float         GetCrimeGold() override;                                                                                                                                                                                        // 0A3
		virtual void          ModCrimeGold(float a_amount) override;                                                                                                                                                                          // 0A4
		virtual float         GetTurningSpeed() override;                                                                                                                                                                                     // 0A5
		virtual TESSkill*     GetHighestSkill() override;                                                                                                                                                                                     // 0AF
		virtual bool          RemoveWornItem(TESBoundObject* a_obj, std::int32_t a_num, ExtraDataList* a_extra, bool a_left, bool a_force) override;                                                                                          // 0BD
		virtual ItemChange*   GetBestWeapon(WEAPON_TYPE a_type) override;                                                                                                                                                                     // 0BE
		virtual ItemChange*   GetBestAmmo() override;                                                                                                                                                                                         // 0BF
		virtual void          ResetArmorRating() override;                                                                                                                                                                                    // 0C0
		virtual bool          InitiateDialogue(Actor* a_target, bool a_flag, TESTopic* a_topic) override;                                                                                                                                     // 0CF
		virtual void          InitiateTrespassPackage(TrespassPackage* a_package) override;                                                                                                                                                   // 0D1
		virtual void          InitiateVampireFeedPackage(Actor* a_target, TESObjectREFR* a_furniture, FurnitureMark* a_marker, std::uint8_t a_index) override;                                                                                // 0D2
		virtual void          EndDialogue() override;                                                                                                                                                                                         // 0D5
		virtual void          InitiateAlarm(Crime* a_crime, std::int32_t a_procedureIndex, bool a_sendAlarm, Actor* a_actor) override;                                                                                                        // 0D6
		virtual void          InitiateSpectator(SpectatorEvent* a_event) override;                                                                                                                                                            // 0D7
		virtual float         GetArmorRating() override;                                                                                                                                                                                      // 0E4
		virtual std::int32_t  GetAttackDamage() override;                                                                                                                                                                                     // 0E5
		virtual bool          IsTrespassing() override;                                                                                                                                                                                       // 0E7
		virtual bool          IsFeeding() override;                                                                                                                                                                                           // 0E8
		virtual bool          IsProcessingTrespassAlarm() override;                                                                                                                                                                           // 0E9
		virtual void          OpponentYields(Actor* a_opponent) override;                                                                                                                                                                     // 0EC
		virtual bool          WouldAcceptYield(Actor* a_opponent) override;                                                                                                                                                                   // 0ED
		virtual void          SetHorse(Creature* a_horse) override;                                                                                                                                                                           // 0F2
		virtual void          DoPreloadPairedActor(VPreloadAssetsHandlers::PRELOAD_PRIORITY a_basePriority, VPreloadAssetsHandlers::PRELOAD_PRIORITY a_higherPriority) override;                                                              // 105
		virtual void          DoPreloadPairedActorAndInventoryItems(VPreloadAssetsHandlers::PRELOAD_PRIORITY a_basePriority, VPreloadAssetsHandlers::PRELOAD_PRIORITY a_higherPriority) override;                                             // 106
		virtual void          DoReleasePairedActorAndInventoryItems() override;                                                                                                                                                               // 107
		virtual void          DoPreloadEarlyUnpairedActor(VPreloadAssetsHandlers::PRELOAD_PRIORITY a_basePriority, VPreloadAssetsHandlers::PRELOAD_PRIORITY a_higherPriority, float a_distanceFromPlayerInMeters) override;                   // 108
		virtual void          DoPreloadEarlyUnpairedActorAndInventoryItems(VPreloadAssetsHandlers::PRELOAD_PRIORITY a_basePriority, VPreloadAssetsHandlers::PRELOAD_PRIORITY a_higherPriority, float a_distanceFromPlayerInMeters) override;  // 109
		virtual void          DoReleaseCachedAssetsForUnpairedActorAndInventoryItems() override;                                                                                                                                              // 10A

		// override (IVPairableItem)
		virtual void OnPrePairItem() override;   // 03
		virtual void OnPostPairItem() override;  // 04

		// members
		BipedAnim* biped;        // 328
		float      armorRating;  // 330
	};
	static_assert(sizeof(Character) == 0x338);
}
