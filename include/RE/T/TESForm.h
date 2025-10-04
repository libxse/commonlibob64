#pragma once

#include "RE/B/BSStringT.h"
#include "RE/B/BSTCaseInsensitiveStringMap.h"
#include "RE/B/BSTList.h"
#include "RE/B/BaseFormComponent.h"
#include "RE/F/FormTypes.h"
#include "RE/N/NiTPointerMap.h"

namespace RE
{
	class ExportTESForm;
	class TESFile;
	class TESBoundObject;
	struct FORM;
	struct FORM_GROUP;

	class TESForm :
		public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI::TESForm;
		inline static constexpr auto VTABLE = VTABLE::TESForm;
		inline static constexpr auto FORMTYPE = FormType::None;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kMaster = 1 << 0,
				kAltered = 1 << 1,
				kLoaded = 1 << 2,
				kInitialized = 1 << 3,
				kOptimized = 1 << 4,
				kDeleted = 1 << 5,
				kBorderRegion = 1 << 6,
				kFireOff = 1 << 7,
				kCastShadows = 1 << 9,
				kEssential = 1 << 10,
				kQuestItem = 1 << 10,
				kDisabled = 1 << 11,
				kIgnored = 1 << 12,
				kTemporary = 1 << 14,
				kMustBeVisibleDistant = 1 << 15,
				kDangerous = 1 << 17,
				kOffLimits = 1 << 17,
				kCompressed = 1 << 18,
				kCantWait = 1 << 19,
				kStartsDead = 1 << 19,
				kIgnoreFriendlyHits = 1 << 20,
			};
		};

		// override (BaseFormComponent)
		virtual void CopyComponent(BaseFormComponent* a_rhs) override;     // 02
		virtual bool CompareComponent(BaseFormComponent* a_rhs) override;  // 03

		// add
		virtual ~TESForm();                                                                                                                                               // 04
		virtual void           InitializeData();                                                                                                                          // 05
		virtual void           ClearData();                                                                                                                               // 06
		virtual bool           Load(TESFile* a_file);                                                                                                                     // 07
		virtual bool           Save(TESFile* a_file);                                                                                                                     // 08
		virtual void           Save();                                                                                                                                    // 09
		virtual bool           LoadEdit(TESFile* a_file);                                                                                                                 // 0A
		virtual bool           SaveEdit(TESFile* a_file);                                                                                                                 // 0B
		virtual bool           SavesBefore(FORM* a_group);                                                                                                                // 0C
		virtual bool           SavesBefore(TESForm* a_form);                                                                                                              // 0D
		virtual TESForm*       CreateDuplicateForm(bool a_createEditorID, NiTPointerMap<TESForm*, TESForm*>* a_copyMap);                                                  // 0E
		virtual void           PostDuplicateProcess(NiTPointerMap<TESForm*, TESForm*>* a_copyMap);                                                                        // 0F
		virtual void           AddChange(std::uint32_t a_changeFlags);                                                                                                    // 10
		virtual void           RemoveChange(std::uint32_t a_changeFlags);                                                                                                 // 11
		virtual void           ForceChange(std::uint32_t a_changeFlags);                                                                                                  // 12
		virtual std::uint16_t  GetSaveSize(std::uint32_t a_changeFlags);                                                                                                  // 13
		virtual void           SaveGame(std::uint32_t a_changeFlags);                                                                                                     // 14
		virtual void           LoadGame(std::uint32_t a_flags, std::uint32_t a_currentFlags);                                                                             // 15
		virtual void           InitLoadGame(std::uint32_t a_flags, std::uint32_t a_oldFlags);                                                                             // 16
		virtual void           FinishInitLoadGame(std::uint32_t a_flags, std::uint32_t a_oldFlags);                                                                       // 17
		virtual void           Revert(std::uint32_t a_flags);                                                                                                             // 18
		virtual void           LoadQueuedFormData(std::uint16_t a_arg01);                                                                                                 // 19
		virtual bool           FindInFileFast(TESFile* a_file);                                                                                                           // 1A
		virtual void           InitItem();                                                                                                                                // 1B
		virtual FormType       GetSavedFormType();                                                                                                                        // 1C
		virtual void           GetFormDetailedString(BSString& a_strOut);                                                                                                 // 1D
		virtual bool           GetQuestObject();                                                                                                                          // 1E
		virtual bool           GetHasSpokenFlag();                                                                                                                        // 1F
		virtual bool           GetHavokDeath();                                                                                                                           // 20
		virtual bool           GetNeedToChangeProcess();                                                                                                                  // 21
		virtual bool           GetDangerous();                                                                                                                            // 22
		virtual void           SetDelete(bool a_set);                                                                                                                     // 23
		virtual void           SetAltered(bool a_set);                                                                                                                    // 24
		virtual void           SetQuestObject(bool a_set);                                                                                                                // 25
		virtual void           SetHasSpokenFlag(bool a_set);                                                                                                              // 26
		virtual void           SetHavokDeath(bool a_set);                                                                                                                 // 27
		virtual void           SetNeedToChangeProcess(bool a_set);                                                                                                        // 28
		virtual bool           IsBoundObject();                                                                                                                           // 29
		virtual bool           IsObject();                                                                                                                                // 2A
		virtual bool           IsMagicItem();                                                                                                                             // 2B
		virtual std::uint32_t  GetRefCount();                                                                                                                             // 2C
		virtual void           Copy(TESForm* a_srcForm);                                                                                                                  // 2D
		virtual bool           Compare(TESForm* a_copyForm);                                                                                                              // 2E
		virtual bool           BelongsInGroup(FORM* a_form, bool a_allowParentGroups, bool a_currentOnly);                                                                // 2F
		virtual void           CreateGroupData(FORM* a_form, FORM_GROUP* a_group);                                                                                        // 30
		virtual bool           IsParentForm();                                                                                                                            // 31
		virtual bool           IsFormTypeChild(FormType a_type);                                                                                                          // 32
		virtual bool           Activate(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, bool a_idFlag, TESBoundObject* a_object, std::int32_t a_targetCount);  // 33
		virtual char*          GetObjectTypeName();                                                                                                                       // 34
		virtual const char*    GetFormEditorID();                                                                                                                         // 35
		virtual bool           SetFormEditorID(const char* a_editorID);                                                                                                   // 36
		virtual std::uint8_t   GetLastLoadFileIndex();                                                                                                                    // 37
		virtual void           FillExportForm(bool a_gameplayOnly);                                                                                                       // 38
		virtual void           UpdateFormValues(const ExportTESForm* a_exportForm);                                                                                       // 39
		virtual ExportTESForm* GetExportForm(bool a_fullLoad);                                                                                                            // 3A
		virtual bool           HasDifferentFormValues(const ExportTESForm* a_exportForm);                                                                                 // 3B

		[[nodiscard]] static auto GetAllForms()
			-> NiTPointerMap<TESFormID, TESForm*>*
		{
			REL::Relocation<NiTPointerMap<TESFormID, TESForm*>*> allForms{ ID::TESForm::AllForms };
			return allForms.get();
		}

		[[nodiscard]] static auto GetAllFormsByEditorID()
			-> BSTCaseInsensitiveStringMap<TESForm*>*
		{
			REL::Relocation<BSTCaseInsensitiveStringMap<TESForm*>*> allFormsByEditorID{ ID::TESForm::AllFormsByEditorID };
			return allFormsByEditorID.get();
		}

		[[nodiscard]] static TESForm* LookupByID(TESFormID a_formID)
		{
			const auto& map = GetAllForms();
			if (map) {
				const auto it = map->find(a_formID);
				return it != map->end() ? it->second : nullptr;
			} else {
				return nullptr;
			}
		}

		template <class T>
		[[nodiscard]] static T* LookupByID(TESFormID a_formID)
		{
			const auto form = LookupByID(a_formID);
			return form ? form->As<T>() : nullptr;
		}

		[[nodiscard]] static TESForm* LookupByEditorID(const std::string_view& a_editorID)
		{
			const auto& map = GetAllFormsByEditorID();
			if (map) {
				const auto it = map->find(a_editorID.data());
				return it != map->end() ? it->second : nullptr;
			} else {
				return nullptr;
			}
		}

		template <class T>
		[[nodiscard]] static T* LookupByEditorID(const std::string_view& a_editorID)
		{
			const auto form = LookupByEditorID(a_editorID);
			return form ? form->As<T>() : nullptr;
		}

		[[nodiscard]] auto      GetFormFlags() const noexcept { return formFlags; }
		[[nodiscard]] TESFormID GetFormID() const noexcept { return formID; }
		[[nodiscard]] FormType  GetFormType() const noexcept { return *formType; }

		[[nodiscard]] bool Is(FormType a_type) const noexcept { return GetFormType() == a_type; }

		template <class... Args>
		[[nodiscard]] bool Is(Args... a_args) const noexcept
			requires(std::same_as<Args, FormType> && ...)
		{
			return (Is(a_args) || ...);
		}

		template <class T>
		[[nodiscard]] bool Is() const noexcept
			requires(std::derived_from<T, TESForm> &&
					 !std::is_pointer_v<T> &&
					 !std::is_reference_v<T>)
		{
			return Is(T::FORMTYPE);
		}

		[[nodiscard]] bool IsAmmo() const noexcept { return Is(FormType::Ammo); }
		[[nodiscard]] bool IsArmor() const noexcept { return Is(FormType::Armor); }
		[[nodiscard]] bool IsBook() const noexcept { return Is(FormType::Book); }
		[[nodiscard]] bool IsDeleted() const noexcept { return (GetFormFlags() & RecordFlags::kDeleted) != 0; }
		[[nodiscard]] bool IsDynamicForm() const noexcept { return GetFormID() >= 0xFF000000; }
		[[nodiscard]] bool IsGold() const noexcept { return GetFormID() == 0x0000000F; }
		[[nodiscard]] bool IsKey() const noexcept { return Is(FormType::KeyMaster); }
		[[nodiscard]] bool IsLockpick() const noexcept { return GetFormID() == 0x0000000A; }

		[[nodiscard]] bool IsNot(FormType a_type) const noexcept { return !Is(a_type); }

		template <class... Args>
		[[nodiscard]] bool IsNot(Args... a_args) const noexcept
			requires(std::same_as<Args, FormType> && ...)
		{
			return (IsNot(a_args) && ...);
		}

		[[nodiscard]] bool IsPlayer() const noexcept { return GetFormID() == 0x00000007; }
		[[nodiscard]] bool IsPlayerRef() const noexcept { return GetFormID() == 0x00000014; }
		[[nodiscard]] bool IsSoulGem() const noexcept { return Is(FormType::SoulGem); }
		[[nodiscard]] bool IsWeapon() const noexcept { return Is(FormType::Weapon); }

		template <class T>
		[[nodiscard]] T* As() noexcept
			requires(std::derived_from<T, TESForm> &&
					 !std::is_pointer_v<T> &&
					 !std::is_reference_v<T>)
		{
			return Is<T>() ? static_cast<T*>(this) : nullptr;
		}

		template <class T>
		[[nodiscard]] const T* As() const noexcept
			requires(std::derived_from<T, TESForm> &&
					 !std::is_pointer_v<T> &&
					 !std::is_reference_v<T>)
		{
			return Is<T>() ? static_cast<const T*>(this) : nullptr;
		}

		// members
		REX::Enum<FormType, std::uint8_t> formType;    // 08
		std::uint32_t                     formFlags;   // 0C
		TESFormID                         formID;      // 10
		BSSimpleList<TESFile*>            files;       // 18
		ExportTESForm*                    exportForm;  // 28
	};
	static_assert(sizeof(TESForm) == 0x30);
}
