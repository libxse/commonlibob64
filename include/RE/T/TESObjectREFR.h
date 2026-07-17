#pragma once

#include "RE/E/EVUnpairingState.h"
#include "RE/E/ExtraDataList.h"
#include "RE/F/FormTypes.h"
#include "RE/I/IVPairableItem.h"
#include "RE/N/NiPointer.h"
#include "RE/O/OBJ_REFR.h"
#include "RE/S/SIT_SLEEP_STATE.h"
#include "RE/T/TESChildCell.h"
#include "RE/T/TESContainer.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESMemContextForm.h"

namespace RE
{
	class Animation;
	class bhkSimpleShapePhantom;
	class BipedAnim;
	class BSAnimGroupSequence;
	class BSFaceGenAnimationData;
	class BSFaceGenNiNode;
	class hkRigidBody;
	class MagicCaster;
	class MagicTarget;
	class NiAVObject;
	class NiNode;
	class TESActorBase;
	class TESObjectCELL;
	class TargetEntry;
	class TrapEntry;

	class TESObjectREFR :
		public TESForm,
		public TESChildCell,
		public IVPairableItem,
		public TESMemContextForm
	{
	public:
		inline static constexpr auto RTTI = RTTI::TESObjectREFR;
		inline static constexpr auto VTABLE = VTABLE::TESObjectREFR;
		inline static constexpr auto FORMTYPE = FormType::Reference;

		struct FVDoorTeleportationInfo
		{
		public:
			// members
			TESObjectREFR*  teleportingDoor;  // 00
			bool            idFlag;           // 08
			TESBoundObject* objectToGet;      // 10
			std::int32_t    count;            // 18
		};
		static_assert(sizeof(FVDoorTeleportationInfo) == 0x20);

		// override (TESForm)
		virtual ~TESObjectREFR() override;                                                                                         // 04
		virtual void           InitializeData() override;                                                                          // 05
		virtual void           ClearData() override;                                                                               // 06
		virtual bool           Load(TESFile* a_file) override;                                                                     // 07
		virtual void           Save() override;                                                                                    // 09
		virtual bool           SavesBefore(FORM* a_group) override;                                                                // 0C
		virtual bool           SavesBefore(TESForm* a_form) override;                                                              // 0D
		virtual TESForm*       CreateDuplicateForm(bool a_createEditorID, NiTPointerMap<TESForm*, TESForm*>* a_copyMap) override;  // 0E
		virtual void           PostDuplicateProcess(NiTPointerMap<TESForm*, TESForm*>* a_copyMap) override;                        // 0F
		virtual std::uint16_t  GetSaveSize(std::uint32_t a_changeFlags) override;                                                  // 13
		virtual void           SaveGame(std::uint32_t a_changeFlags) override;                                                     // 14
		virtual void           LoadGame(std::uint32_t a_flags, std::uint32_t a_currentFlags) override;                             // 15
		virtual void           InitLoadGame(std::uint32_t a_flags, std::uint32_t a_oldFlags) override;                             // 16
		virtual void           FinishInitLoadGame(std::uint32_t a_flags, std::uint32_t a_oldFlags) override;                       // 17
		virtual void           Revert(std::uint32_t a_flags) override;                                                             // 18
		virtual void           InitItem() override;                                                                                // 1B
		virtual FormType       GetSavedFormType() override;                                                                        // 1C
		virtual void           GetFormDetailedString(BSString& a_strOut) override;                                                 // 1D
		virtual bool           GetQuestObject() override;                                                                          // 1E
		virtual bool           GetDangerous() override;                                                                            // 22
		virtual void           SetDelete(bool a_set) override;                                                                     // 23
		virtual void           SetAltered(bool a_set) override;                                                                    // 24
		virtual void           Copy(TESForm* a_srcForm) override;                                                                  // 2D
		virtual bool           Compare(TESForm* a_copyForm) override;                                                              // 2E
		virtual bool           BelongsInGroup(FORM* a_form, bool a_allowParentGroups, bool a_currentOnly) override;                // 2F
		virtual void           CreateGroupData(FORM* a_form, FORM_GROUP* a_group) override;                                        // 30
		virtual const char*    GetFormEditorID() override;                                                                         // 35
		virtual std::uint8_t   GetLastLoadFileIndex() override;                                                                    // 37
		virtual void           FillExportForm(bool a_gameplayOnly) override;                                                       // 38
		virtual ExportTESForm* GetExportForm(bool a_fullLoad) override;                                                            // 3A

		// override (TESChildCell)
		virtual TESObjectCELL* GetSaveParentCell() override;  // 00

		// override (IVPairableItem)
		virtual bool ShouldBePaired() override;     // 00
		virtual void ProcessPairItem() override;    // 01
		virtual void ProcessUnpairItem() override;  // 02
		virtual void OnPrePairItem() override;      // 03
		virtual void OnPostPairItem() override;     // 04
		virtual void OnPreUnpairItem() override;    // 05
		virtual void OnPostUnpairItem() override;   // 06

		// add
		virtual float                   VoiceSoundFunction(TESTopic* a_topic, Actor* a_target, bool a_playerHead, bool a_alwaysPlay, bool a_forceCorrectDuration);                                                                                                         // 3C
		virtual bool                    GetCastShadows();                                                                                                                                                                                                                  // 3D
		virtual void                    SetCastShadows(bool a_value);                                                                                                                                                                                                      // 3E
		virtual bool                    IsProjectile();                                                                                                                                                                                                                    // 3F
		virtual float                   GetScale();                                                                                                                                                                                                                        // 40
		virtual NiPoint3*               GetStartingAngle();                                                                                                                                                                                                                // 41
		virtual NiPoint3*               GetStartingLocation();                                                                                                                                                                                                             // 42
		virtual void                    SetStartingPosition(NiPoint3 a_position);                                                                                                                                                                                          // 43
		virtual void                    UpdateRefLight();                                                                                                                                                                                                                  // 44
		virtual void                    AddBoundObjectItem(TESBoundObject* a_object, ExtraDataList* a_extra, std::int32_t a_number);                                                                                                                                       // 45
		virtual TESObjectREFR*          RemoveItem(TESBoundObject* a_object, ExtraDataList* a_extra, std::int32_t a_number, bool a_stealing, bool a_dropWorld, TESObjectREFR* a_containerObj, NiPoint3* a_point, NiPoint3* a_rotate, bool a_delete, bool a_preferStolen);  // 46
		virtual void                    RemoveItemType(FormType a_type, bool a_stealing, std::int32_t a_number);                                                                                                                                                           // 47
		virtual bool                    AddWornItem(TESBoundObject* a_object, std::int32_t a_number, ExtraDataList* a_extra, bool a_forceEquip);                                                                                                                           // 48
		virtual bool                    RemoveWornItem(TESBoundObject* a_object, std::int32_t a_number, ExtraDataList* a_extra);                                                                                                                                           // 49
		virtual void                    DoTrap(TrapEntry* a_trap, TargetEntry* a_target);                                                                                                                                                                                  // 4A
		virtual void                    AddObjectToContainer(TESBoundObject* a_obj, ExtraDataList* a_extra, std::int32_t a_count);                                                                                                                                         // 4B
		virtual void                    ReturnToOblivionEntryPoint();                                                                                                                                                                                                      // 4C
		virtual NiPoint3*               GetLookingAtLocation();                                                                                                                                                                                                            // 4D
		virtual MagicCaster*            GetMagicCaster();                                                                                                                                                                                                                  // 4E
		virtual MagicTarget*            GetMagicTarget();                                                                                                                                                                                                                  // 4F
		virtual TESActorBase*           GetTemplateActorBase();                                                                                                                                                                                                            // 50
		virtual void                    SetTemplateActorBase(TESActorBase* a_template);                                                                                                                                                                                    // 51
		virtual BSFaceGenNiNode*        GetFaceNodeBiped(NiNode* a_headNode);                                                                                                                                                                                              // 52
		virtual BSFaceGenNiNode*        GetFaceNodeSkinned(NiNode* a_headNode);                                                                                                                                                                                            // 53
		virtual BSFaceGenNiNode*        GetFaceNode(NiNode* a_headNode);                                                                                                                                                                                                   // 54
		virtual BSFaceGenAnimationData* GetFaceAnimationData(NiNode* a_headNode);                                                                                                                                                                                          // 55
		virtual bool                    ClampToGround();                                                                                                                                                                                                                   // 56
		virtual bool                    DetachHavok();                                                                                                                                                                                                                     // 57
		virtual void                    InitHavok();                                                                                                                                                                                                                       // 58
		virtual NiAVObject*             Load3D();                                                                                                                                                                                                                          // 59
		virtual void                    Set3D(NiAVObject* a_node);                                                                                                                                                                                                         // 5A
		virtual NiAVObject*             Get3D();                                                                                                                                                                                                                           // 5B
		virtual NiPoint3*               GetBoundMin();                                                                                                                                                                                                                     // 5C
		virtual NiPoint3*               GetBoundMax();                                                                                                                                                                                                                     // 5D
		virtual void                    UpdateAnimation();                                                                                                                                                                                                                 // 5E
		virtual Animation*              GetAnimation();                                                                                                                                                                                                                    // 5F
		virtual BipedAnim*              GetBiped();                                                                                                                                                                                                                        // 60
		virtual void                    SetBiped(BipedAnim* a_biped);                                                                                                                                                                                                      // 61
		virtual TESBoundObject*         GetObjectReference();                                                                                                                                                                                                              // 62
		virtual const NiPoint3*         GetLocationOnReference();                                                                                                                                                                                                          // 63
		virtual void                    MoveHavok(bool a_forceRecurse);                                                                                                                                                                                                    // 64
		virtual void                    SetActionComplete(bool a_value);                                                                                                                                                                                                   // 65
		virtual void                    SetMovementComplete(bool a_value);                                                                                                                                                                                                 // 66
		virtual void                    ResetInventory(bool a_leveledOnly);                                                                                                                                                                                                // 67
		virtual bool                    IsMobileObject();                                                                                                                                                                                                                  // 68
		virtual SIT_SLEEP_STATE         GetSitSleepState();                                                                                                                                                                                                                // 69
		virtual bool                    IsActor();                                                                                                                                                                                                                         // 6A
		virtual void                    SetParentCell(TESObjectCELL* a_cell);                                                                                                                                                                                              // 6B
		virtual bool                    IsDead(bool a_notEssential);                                                                                                                                                                                                       // 6C
		virtual bool                    IsKnockedOut();                                                                                                                                                                                                                    // 6D
		virtual bool                    IsParalyzed();                                                                                                                                                                                                                     // 6E
		virtual void                    OnModelAttached();                                                                                                                                                                                                                 // 6F
		virtual void                    OnModelDeattached();                                                                                                                                                                                                               // 70
		virtual void                    OnPostModelAttached();                                                                                                                                                                                                             // 71
		virtual void                    OnEnabled();                                                                                                                                                                                                                       // 72
		virtual void                    OnDisabled();                                                                                                                                                                                                                      // 73
		virtual bool                    IsPairable();                                                                                                                                                                                                                      // 74
		virtual void                    PairAnimationInitialization(const BSAnimGroupSequence* a_lastFinishedSequence);                                                                                                                                                    // 75
		virtual void                    SendPositionPairingHandler();                                                                                                                                                                                                      // 76

		bool GetInterior()
		{
			using func_t = decltype(&TESObjectREFR::GetInterior);
			static REL::Relocation<func_t> func{ ID::TESObjectREFR::GetInterior };
			return func(this);
		}

		TESWorldSpace* GetWorldSpace()
		{
			using func_t = decltype(&TESObjectREFR::GetWorldSpace);
			static REL::Relocation<func_t> func{ ID::TESObjectREFR::GetWorldSpace };
			return func(this);
		}

		// members
		OBJ_REFR                data;                                   // 050
		float                   refScale;                               // 070
		NiPointer<NiAVObject>   data3D;                                 // 078
		TESObjectCELL*          parentCell;                             // 080
		ExtraDataList           extra;                                  // 088
		std::uint32_t           asyncFlowHash;                          // 0A8
		bool                    isOblivionRefLoaded;                    // 0AC
		bool                    isAltarRefLoaded;                       // 0AD
		hkRigidBody*            altarFakeRigidBody;                     // 0B0
		bhkSimpleShapePhantom*  altarFakePhantom;                       // 0B8
		bool                    hasTrapContinuityBeenCheckedInReverse;  // 0C0
		TESObjectREFR*          dockedActor;                            // 0C8
		EVUnpairingState        unpairingState;                         // 0D0
		UE::VPairingEntry*      droppedBy;                              // 0D8
		bool                    isBeingTeleported;                      // 0E0
		FVDoorTeleportationInfo pendingDoorTeleportationInfo;           // 0E8
		std::uint32_t           levelCreatureFormID;                    // 108
		TESContainer            chosenCreatures;                        // 110
		bool                    isContainerInit;                        // 130
		std::uint8_t            lastLoadFileCompileIndex;               // 131
	};
	static_assert(sizeof(TESObjectREFR) == 0x138);
}
