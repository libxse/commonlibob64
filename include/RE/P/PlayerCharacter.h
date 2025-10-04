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
		bool                                 hasGrabbedObject;                // 338
		bool                                 aiContinuePickup;                // 339
		std::int32_t                         combatPursue;                    // 33C
		bool                                 travelUseDoor;                   // 340
		bool                                 onElevator;                      // 341
		bool                                 inSEWorld;                       // 342
		bool                                 forceQuestTargetUpdate;          // 343
		DialoguePackage*                     closesConversation;              // 348
		std::int32_t                         buyPercent;                      // 350
		std::int32_t                         sellPercent;                     // 354
		bool                                 inBarter;                        // 358
		Actor*                               barterContainer;                 // 360
		bool                                 transporting;                    // 368
		float                                grantedPlayerXP;                 // 36C
		float                                skillUsage[21];                  // 370
		std::int32_t                         skillAdvanceCount;               // 3C4
		std::int32_t                         skillLevels[21];                 // 3C8
		bool                                 readyToLevelUp;                  // 41C
		Creature*                            lastRiddenHorse;                 // 420
		PlayerDeathInfos                     playerDeathInfos;                // 428
		BSSimpleList<ActiveEffect*>*         activeEffectList;                // 438
		MagicItem*                           currentSpell;                    // 440
		MagicTarget*                         desiredTarget;                   // 448
		CameraCaster*                        cameraCaster;                    // 450
		HitCaster*                           hitCaster;                       // 458
		BSSimpleList<MagicItem*>*            eatDrinkItems;                   // 460
		BSSimpleList<TESBoundObject*>*       queuedWornEnchantments;          // 468
		bool                                 showQuestItemsInInventory;       // 470
		float                                magicActorValueModifiers[72];    // 474
		float                                scriptActorValueModifiers[72];   // 594
		float                                healthModifier;                  // 6B4
		float                                magickaModifier;                 // 6B8
		float                                fatigueModifier;                 // 6BC
		float                                gameActorValueModifiers[72];     // 6C0
		TESObjectREFR*                       lastDoorActivated;               // 7E0
		NiPointer<bhkMouseSpringAction>      grabSpring;                      // 7E8
		TESObjectREFR*                       grabbedObject;                   // 7F0
		GrabbingType                         grabType;                        // 7F8
		float                                grabObjectWeight;                // 7FC
		float                                grabDistance;                    // 800
		bool                                 is3rdPerson;                     // 804
		bool                                 temp3rdPerson;                   // 805
		bool                                 temp3rdPersonSwitchBack;         // 806
		bool                                 alwaysRun;                       // 807
		bool                                 autoMove;                        // 808
		std::int32_t                         sleepTime;                       // 80C
		bool                                 isSleeping;                      // 810
		float                                fov;                             // 814
		float                                secondRunning;                   // 818
		float                                secondSwimming;                  // 81C
		float                                secondSneaking;                  // 820
		bool                                 actorInSneakRange;               // 824
		bool                                 canFastTravel;                   // 825
		BSSimpleList<TESObjectREFR*>*        playerCombatList;                // 828
		float*                               chargenSkillUses;                // 830
		BSSimpleList<AttributeSkillCounts*>* attributeSkillCounts;            // 838
		char                                 specializationCount[3];          // 840
		std::int32_t                         numberTraining;                  // 844
		bool                                 controlsDisabled;                // 848
		TESObjectREFR*                       forceActivateRef;                // 850
		BipedAnim*                           firstPersonBipedAnim;            // 858
		Animation*                           firstPersonAnimation;            // 860
		NiPointer<NiAVObject>                firstPerson3D;                   // 868
		float                                eyeHeight;                       // 870
		NiPointer<NiNode>                    inventoryPC;                     // 878
		Animation*                           inventoryAnimation;              // 880
		MagicShaderHitEffect*                inventoryWeaponEffect;           // 888
		BSSimpleList<TESTopic*>              listTopics;                      // 890
		BSSimpleList<TESQuestStageItem*>     listQuestLog;                    // 8A0
		TESQuest*                            activeQuest;                     // 8B0
		BSSimpleList<TESQuestTarget*>        listQuestTargets;                // 8B8
		bool                                 greetingPlayer;                  // 8C8
		float                                greetTimer;                      // 8CC
		std::int32_t                         daysInPrison;                    // 8D0
		std::int32_t                         hoursToSleep;                    // 8D4
		bool                                 escapedFromJail;                 // 8D8
		std::uint8_t                         murder;                          // 8D9
		std::int32_t                         amountStolenSold;                // 8DC
		float                                sortActorDistanceTimer;          // 8E0
		float                                sitHeadingDelta;                 // 8E4
		bool                                 beenAttacked;                    // 8E8
		MagicItem*                           selectedSpell;                   // 8F0
		TESObjectBOOK*                       selectedScroll;                  // 8F8
		NiPoint3                             playerMapMarkerLoc;              // 900
		TESForm*                             playerMapMarkerSpace;            // 910
		TESObjectREFR*                       playerMapMarkerDoor;             // 918
		float                                bowTimer;                        // 920
		BirthSign*                           birthSign;                       // 928
		std::int32_t                         numAdvance;                      // 930
		std::uint8_t                         skillAdvance[4];                 // 934
		TESClass*                            defaultClass;                    // 938
		TESClass*                            classBasedOn;                    // 940
		std::uint32_t                        miscStats[28];                   // 948
		std::uint32_t                        crimeCounts[6];                  // 9B8
		AlchemyItem*                         pendingPoison;                   // 9D0
		bool                                 vampireFed;                      // 9D8
		bool                                 chargen;                         // 9D9
		bool                                 telekinesisSelected;             // 9DA
		TESRegion*                           occupiedRegion;                  // 9E0
		BSSimpleList<TESRegionSound*>        currentRegionSoundList;          // 9E8
		std::int32_t                         pcFame;                          // 9F8
		std::int32_t                         pcInfamy;                        // 9FC
		std::int32_t                         crimeGoldAcum;                   // A00
		float                                crimeGoldSE;                     // A04
		BSSimpleList<TESObjectREFR*>         jailMarkerList;                  // A08
		void*                                initialStateBuffer;              // A18
		std::uint32_t                        lastPlayingTimeUpdate;           // A20
		std::uint32_t                        totalPlayingTime;                // A24
		std::uint32_t                        characterSeed;                   // A28
		bool                                 aiControlledToPos;               // A2C
		bool                                 aiControlledFromPos;             // A2D
		bool                                 inBorderContainedCell;           // A2E
		bool                                 returnToLastKnownGoodPosition;   // A2F
		NiPoint3                             lastKnownGoodPosition;           // A30
		TESForm*                             lastKnownGoodLocation;           // A40
		NiTArray<TESRegion*>*                borderRegions;                   // A48
		float                                difficultyLevel;                 // A50
		std::uint32_t                        unkA54;                          // A54 - new
		std::uint32_t                        unkA58;                          // A58 - new
		bool                                 beingChased;                     // A5C
		BSSimpleList<MAP_MARKER_STRUCT*>     mapMarkerList;                   // A60
		TESWorldSpace*                       mapWorld;                        // A70
		bool                                 ufoMode;                         // A78
		float                                ufoCameraHeading;                // A7C
		float                                ufoCameraPitch;                  // A80
		NiPoint3                             ufoCameraPos;                    // A84
		std::uint32_t                        selectedSpellCastSoundID;        // A90
		TESGameSoundHandle*                  selectedSpellCastSound;          // A98
		TESGameSoundHandle*                  magicFailureSounds[6];           // AA0
		BSSimpleList<TESObjectREFR*>         droppedRefList;                  // AD0
		NiTMap<std::uint32_t, std::uint8_t>  randomDoorSpaceMap;              // AE0
		NiPointer<NiPointLight>              firstPersonLight;                // B00
		NiPointer<NiPointLight>              thirdPersonLight;                // B08
		std::int32_t                         numberActorsInCombat;            // B10
		float                                skillAdvancementUses[21];        // B14
		bool                                 loadingFromMainMenu;             // B68
		bool                                 insufficientChargeMessageShown;  // B69
		float                                dropAngleMod;                    // B6C
		float                                lastDropAngleMod;                // B70
		float                                playerDeathReloadTime;           // B74
		bool                                 shouldRefreshClairvoyance;       // B78
		NiPointer<NiCamera>                  chaseCameraPtr;                  // B80
	};
	static_assert(sizeof(PlayerCharacter) == 0xB88);
}
