#pragma once

#include "RE/C/Character.h"
#include "RE/N/NiTArray.h"
#include "RE/P/PlayerDeathInfos.h"

namespace RE
{
	class AttributeSkillCounts;
	class bhkMouseSpringAction;
	class CameraCaster;
	class DialoguePackage;
	class HitCaster;
	class MagicShaderHitEffect;
	class NiCamera;
	class NiPointLight;
	class TESGameSoundHandle;
	class TESQuestStageItem;
	class TESQuestTarget;
	class TESRegionSound;
	struct MAP_MARKER_STRUCT;

	class PlayerCharacter :
		public Character
	{
	public:
		inline static constexpr auto RTTI = RTTI::PlayerCharacter;
		inline static constexpr auto VTABLE = VTABLE::PlayerCharacter;
		inline static constexpr auto FORMTYPE = FormType::ActorCharacter;

		enum class GrabbingType : std::int32_t
		{
			kNone,
			kNormal,
			kInventoryDrop,
			kTelekinesis
		};

		// override (TESForm)
		virtual ~PlayerCharacter() override;                                                                                                                              // 004
		virtual std::uint16_t     GetSaveSize(std::uint32_t a_changeFlags) override;                                                                                      // 013
		virtual void              SaveGame(std::uint32_t a_changeFlags) override;                                                                                         // 014
		virtual void              LoadGame(std::uint32_t a_flags, std::uint32_t a_currentFlags) override;                                                                 // 015
		virtual void              InitLoadGame(std::uint32_t a_flags, std::uint32_t a_oldFlags) override;                                                                 // 016
		virtual void              FinishInitLoadGame(std::uint32_t a_flags, std::uint32_t a_oldFlags) override;                                                           // 017
		virtual void              Revert(std::uint32_t a_flags) override;                                                                                                 // 018
		virtual void              UpdateRefLight() override;                                                                                                              // 044
		virtual void              ReturnToOblivionEntryPoint() override;                                                                                                  // 04C
		virtual NiPoint3*         GetLookingAtLocation() override;                                                                                                        // 04D
		virtual NiAVObject*       Load3D() override;                                                                                                                      // 059
		virtual void              Set3D(NiAVObject* a_node) override;                                                                                                     // 05A
		virtual NiAVObject*       Get3D() override;                                                                                                                       // 05B
		virtual void              UpdateAnimation() override;                                                                                                             // 05E
		virtual Animation*        GetAnimation() override;                                                                                                                // 05F
		virtual BipedAnim*        GetBiped() override;                                                                                                                    // 060
		virtual void              SetParentCell(TESObjectCELL* a_cell) override;                                                                                          // 06B
		virtual void              OnModelAttached() override;                                                                                                             // 06F
		virtual float             GetHeading() override;                                                                                                                  // 087
		virtual std::int32_t      GetFame() override;                                                                                                                     // 090
		virtual std::int32_t      GetInfamy() override;                                                                                                                   // 091
		virtual void              Resurrect(bool a_resetInventory, bool a_attach3D, bool a_getUp) override;                                                               // 092
		virtual void              SetAdvanceNumber(std::int32_t a_number) override;                                                                                       // 093
		virtual std::int32_t      GetAdvanceNumber() override;                                                                                                            // 094
		virtual void              SetSkillAdvanceDelayed(ActorValue::Index a_skill) override;                                                                             // 095
		virtual ActorValue::Index GetSkillAdvanceDelayed() override;                                                                                                      // 096
		virtual void              Update(float a_delta) override;                                                                                                         // 099
		virtual void              InitiateMountHorsePackage(Creature* a_horse) override;                                                                                  // 09A
		virtual void              InitiateDismountHorsePackage() override;                                                                                                // 09B
		virtual void              SetDialogueWithPlayer(bool a_value) override;                                                                                           // 09C
		virtual bool              IsOverEncumbered() override;                                                                                                            // 0A6
		virtual bool              GetVampireFed() override;                                                                                                               // 0A7
		virtual void              SetVampireFed(bool a_value) override;                                                                                                   // 0A8
		virtual BirthSign*        GetBirthSign() override;                                                                                                                // 0A9
		virtual float             GetReach() override;                                                                                                                    // 0AA
		virtual std::int32_t      GetActorValue(ActorValue::Index a_index) override;                                                                                      // 0B0
		virtual float             GetActorFloatValue(ActorValue::Index a_index) override;                                                                                 // 0B1
		virtual void              SetActorValue(ActorValue::Index a_index, float a_value) override;                                                                       // 0B2
		virtual void              SetActorValue(ActorValue::Index a_index, std::int32_t a_value) override;                                                                // 0B3
		virtual void              MagicModActorValue(ActorValue::Index a_index, float a_value, Actor* a_attacker) override;                                               // 0B4
		virtual void              MagicModActorValue(ActorValue::Index a_index, std::int32_t a_value, Actor* a_attacker) override;                                        // 0B5
		virtual void              ScriptModActorValue(ActorValue::Index a_index, float a_value, Actor* a_attacker) override;                                              // 0B6
		virtual void              ScriptModActorValue(ActorValue::Index a_index, std::int32_t a_value, Actor* a_attacker) override;                                       // 0B7
		virtual void              GameModActorValue(ActorValue::Index a_index, float a_value, Actor* a_attacker, bool a_canStopNaturalRegen) override;                    // 0B8
		virtual void              GameModActorValue(ActorValue::Index a_index, std::int32_t a_value, Actor* a_attacker, bool a_canStopNaturalRegen) override;             // 0B9
		virtual void              ModActorBaseValue(ActorValue::Index a_index, float a_value) override;                                                                   // 0BA
		virtual void              ModActorBaseValue(ActorValue::Index a_index, std::int32_t a_value) override;                                                            // 0BB
		virtual bool              DamageEquipment(ItemChange* a_equipment, float a_damage, bool a_ignoreArmorSkill) override;                                             // 0C1
		virtual TESObjectREFR*    DropObject(TESObject* a_obj, ExtraDataList* a_extra, std::int32_t a_number, NiPoint3* a_point, NiPoint3* a_rotate) override;            // 0C2
		virtual void              PickUpObject(TESObjectREFR* a_obj, std::int32_t a_count, bool a_flag) override;                                                         // 0C3
		virtual void              CastScroll(TESObjectBOOK* a_scroll, MagicTarget* a_target) override;                                                                    // 0C4
		virtual bool              CheckCastWhenStrikesEnchantment(ItemChange* a_weapon, Actor* a_target, ArrowProjectile* a_arrow, bool* a_insufficientCharge) override;  // 0C5
		virtual void              CheckStaffEnchantment(ItemChange* a_staff) override;                                                                                    // 0C7
		virtual bool              AddSpell(SpellItem* a_spell) override;                                                                                                  // 0C8
		virtual bool              RemoveSpell(SpellItem* a_spell) override;                                                                                               // 0C9
		virtual void              UseAmmo() override;                                                                                                                     // 0CC
		virtual void              CleanOrphanedMagicModifiers() override;                                                                                                 // 0CD
		virtual bool              IsInCombatWithGuard() override;                                                                                                         // 0CE
		virtual void              InitiateVampireFeedPackage(Actor* a_target, TESObjectREFR* a_furniture, FurnitureMark* a_marker, std::uint8_t a_index) override;        // 0D2
		virtual void              CombatVocalization(Actor* a_target, std::int32_t a_dialogueTopic, bool a_interrupt) override;                                           // 0D4
		virtual void              InitiateGetUpPackage() override;                                                                                                        // 0DA
		virtual void              SetAlpha(float a_value) override;                                                                                                       // 0DB
		virtual float             GetAlpha() override;                                                                                                                    // 0DC
		virtual bool              WouldAcceptYield(Actor* a_opponent) override;                                                                                           // 0ED
		virtual bool              HasBeenAttacked() override;                                                                                                             // 0F5
		virtual void              SetBeenAttacked(bool a_value) override;                                                                                                 // 0F6
		virtual void              UseSkill(ActorValue::Index a_index, SKILL_ACTION a_action, float a_modifier) override;                                                  // 0F8
		virtual void              UseSkillWithSpellCost(ActorValue::Index a_index, float a_spellCost) override;                                                           // 0FA
		virtual void              SpecialDynamicIdleAnimationPairing() override;                                                                                          // 0FD
		virtual void              StartAnimOn1stPerson(std::uint16_t a_animGroup, ACTION_FLAGS a_flags) override;                                                         // 10B
		virtual void              HandleHealthDamage(Actor* a_attacker, float a_damage) override;                                                                         // 111

		// override (IVPairableItem)
		virtual void ProcessPairItem() override;  // 01

		// override (MagicCaster)
		virtual void         CastAbility(SpellItem* a_spell, bool a_loadCast) override;                                                                      // 01
		virtual void         TransferDisease(SpellItem*, MagicTarget* a_desiredTarget, bool a_loadCast) override;                                            // 02
		virtual MagicTarget* GetTouchTarget() override;                                                                                                      // 04
		virtual bool         CheckCast(MagicItem* a_spell, float* a_effectStrength, MagicItem::CannotCastReason* a_reason, bool a_useBaseMagicka) override;  // 08
		virtual float        GetMagicEffectivenessModifier(bool a_justArmor, float a_useThisFatigue) override;                                               // 0C
		virtual void         SetCurrentSpell(MagicItem* a_currentSpell) override;                                                                            // 0E
		virtual MagicTarget* GetDesiredTarget() override;                                                                                                    // 0F
		virtual void         SetDesiredTarget(MagicTarget* a_desiredTarget) override;                                                                        // 10

		// override (MagicTarget)
		virtual bool                         AddTarget(MagicCaster* a_caster, MagicItem* a_spell, ActiveEffect* a_activeEffect, bool a_areaTarget) override;  // 00
		virtual BSSimpleList<ActiveEffect*>* GetActiveEffectList() override;                                                                                  // 02

		static PlayerCharacter* GetSingleton()
		{
			static REL::Relocation<PlayerCharacter**> singleton{ ID::PlayerCharacter::Singleton };
			return *singleton;
		}

		// members
		bool                                 hasGrabbedObject;                // 328
		bool                                 aiContinuePickup;                // 329
		std::int32_t                         combatPursue;                    // 32C
		bool                                 travelUseDoor;                   // 330
		bool                                 onElevator;                      // 331
		bool                                 inSEWorld;                       // 332
		bool                                 forceQuestTargetUpdate;          // 333
		DialoguePackage*                     closesConversation;              // 338
		std::int32_t                         buyPercent;                      // 340
		std::int32_t                         sellPercent;                     // 344
		bool                                 inBarter;                        // 348
		Actor*                               barterContainer;                 // 350
		bool                                 transporting;                    // 358
		float                                grantedPlayerXP;                 // 35C
		float                                skillUsage[21];                  // 360
		std::int32_t                         skillAdvanceCount;               // 3B4
		std::int32_t                         skillLevels[21];                 // 3B8
		bool                                 readyToLevelUp;                  // 40C
		Creature*                            lastRiddenHorse;                 // 410
		PlayerDeathInfos                     playerDeathInfos;                // 418
		BSSimpleList<ActiveEffect*>*         activeEffectList;                // 428
		MagicItem*                           currentSpell;                    // 430
		MagicTarget*                         desiredTarget;                   // 438
		CameraCaster*                        cameraCaster;                    // 440
		HitCaster*                           hitCaster;                       // 448
		BSSimpleList<MagicItem*>*            eatDrinkItems;                   // 450
		BSSimpleList<TESBoundObject*>*       queuedWornEnchantments;          // 458
		bool                                 showQuestItemsInInventory;       // 460
		float                                magicActorValueModifiers[72];    // 464
		float                                scriptActorValueModifiers[72];   // 584
		float                                healthModifier;                  // 6A4
		float                                magickaModifier;                 // 6A8
		float                                fatigueModifier;                 // 6AC
		float                                gameActorValueModifiers[72];     // 6B0
		TESObjectREFR*                       lastDoorActivated;               // 7D0
		NiPointer<bhkMouseSpringAction>      grabSpring;                      // 7D8
		TESObjectREFR*                       grabbedObject;                   // 7E0
		GrabbingType                         grabType;                        // 7E8
		float                                grabObjectWeight;                // 7EC
		float                                grabDistance;                    // 7F0
		bool                                 is3rdPerson;                     // 7F4
		bool                                 temp3rdPerson;                   // 7F5
		bool                                 temp3rdPersonSwitchBack;         // 7F6
		bool                                 alwaysRun;                       // 7F7
		bool                                 autoMove;                        // 7F8
		std::int32_t                         sleepTime;                       // 7FC
		bool                                 isSleeping;                      // 800
		float                                fov;                             // 804
		float                                secondRunning;                   // 808
		float                                secondSwimming;                  // 80C
		float                                secondSneaking;                  // 810
		bool                                 actorInSneakRange;               // 814
		bool                                 canFastTravel;                   // 815
		BSSimpleList<TESObjectREFR*>*        playerCombatList;                // 818
		float*                               chargenSkillUses;                // 820
		BSSimpleList<AttributeSkillCounts*>* attributeSkillCounts;            // 828
		char                                 specializationCount[3];          // 830
		std::int32_t                         numberTraining;                  // 834
		bool                                 controlsDisabled;                // 838
		TESObjectREFR*                       forceActivateRef;                // 840
		BipedAnim*                           _1stPersonBipedAnim;             // 848
		Animation*                           _1stPersonAnimation;             // 850
		NiPointer<NiAVObject>                _1stPerson3D;                    // 858
		float                                eyeHeight;                       // 860
		NiPointer<NiNode>                    inventoryPC;                     // 868
		Animation*                           inventoryAnimation;              // 870
		MagicShaderHitEffect*                inventoryWeaponEffect;           // 878
		BSSimpleList<TESTopic*>              listTopics;                      // 880
		BSSimpleList<TESQuestStageItem*>     listQuestLog;                    // 890
		TESQuest*                            activeQuest;                     // 8A0
		BSSimpleList<TESQuestTarget*>        listQuestTargets;                // 8A8
		bool                                 greetingPlayer;                  // 8B8
		float                                greetTimer;                      // 8BC
		std::int32_t                         daysInPrison;                    // 8C0
		std::int32_t                         hoursToSleep;                    // 8C4
		bool                                 escapedFromJail;                 // 8C8
		std::uint8_t                         murder;                          // 8C9
		std::int32_t                         amountStolenSold;                // 8CC
		float                                sortActorDistanceTimer;          // 8D0
		float                                sitHeadingDelta;                 // 8D4
		bool                                 beenAttacked;                    // 8D8
		MagicItem*                           selectedSpell;                   // 8E0
		TESObjectBOOK*                       selectedScroll;                  // 8E8
		NiPoint3                             playerMapMarkerLoc;              // 8F0
		TESForm*                             playerMapMarkerSpace;            // 900
		TESObjectREFR*                       playerMapMarkerDoor;             // 908
		float                                bowTimer;                        // 910
		BirthSign*                           birthSign;                       // 918
		std::int32_t                         numAdvance;                      // 920
		std::uint8_t                         skillAdvance[4];                 // 924
		TESClass*                            defaultClass;                    // 928
		TESClass*                            classBasedOn;                    // 930
		std::uint32_t                        miscStats[28];                   // 938
		std::uint32_t                        crimeCounts[6];                  // 9A8
		AlchemyItem*                         pendingPoison;                   // 9C0
		bool                                 vampireFed;                      // 9C8
		bool                                 chargen;                         // 9C9
		bool                                 telekinesisSelected;             // 9CA
		TESRegion*                           occupiedRegion;                  // 9D0
		BSSimpleList<TESRegionSound*>        currentRegionSoundList;          // 9D8
		std::int32_t                         pcFame;                          // 9E8
		std::int32_t                         pcInfamy;                        // 9EC
		std::int32_t                         crimeGoldAcum;                   // 9F0
		float                                crimeGoldSE;                     // 9F4
		BSSimpleList<TESObjectREFR*>         jailMarkerList;                  // 9F8
		void*                                initialStateBuffer;              // A08
		std::uint32_t                        lastPlayingTimeUpdate;           // A10
		std::uint32_t                        totalPlayingTime;                // A14
		std::uint32_t                        characterSeed;                   // A18
		bool                                 aiControlledToPos;               // A1C
		bool                                 aiControlledFromPos;             // A1D
		bool                                 inBorderContainedCell;           // A1E
		bool                                 returnToLastKnownGoodPosition;   // A1F
		NiPoint3                             lastKnownGoodPosition;           // A20
		TESForm*                             lastKnownGoodLocation;           // A30
		NiTArray<TESRegion*>*                borderRegions;                   // A38
		float                                difficultyLevel;                 // A40
		bool                                 beingChased;                     // A44
		BSSimpleList<MAP_MARKER_STRUCT*>     mapMarkerList;                   // A48
		TESWorldSpace*                       mapWorld;                        // A58
		bool                                 ufoMode;                         // A60
		float                                ufoCameraHeading;                // A64
		float                                ufoCameraPitch;                  // A68
		NiPoint3                             ufoCameraPos;                    // A6C
		std::uint32_t                        selectedSpellCastSoundID;        // A78
		TESGameSoundHandle*                  selectedSpellCastSound;          // A80
		TESGameSoundHandle*                  magicFailureSounds[6];           // A88
		BSSimpleList<TESObjectREFR*>         droppedRefList;                  // AB8
		NiTMap<std::uint32_t, std::uint8_t>  randomDoorSpaceMap;              // AC8
		NiPointer<NiPointLight>              _1stPersonLight;                 // AE8
		NiPointer<NiPointLight>              _3rdPersonLight;                 // AF0
		std::int32_t                         numberActorsInCombat;            // AF8
		float                                skillAdvancementUses[21];        // AFC
		bool                                 loadingFromMainMenu;             // B50
		bool                                 insufficientChargeMessageShown;  // B51
		float                                dropAngleMod;                    // B54
		float                                lastDropAngleMod;                // B58
		float                                playerDeathReloadTime;           // B5C
		bool                                 shouldRefreshClairvoyance;       // B60
		NiPointer<NiCamera>                  chaseCameraPtr;                  // B68
	};
	static_assert(sizeof(PlayerCharacter) == 0xB70);
}
