#pragma once

#include "RE/O/OBJ_WEAP.h"
#include "RE/T/TESAttackDamageForm.h"
#include "RE/T/TESBoundObject.h"
#include "RE/T/TESEnchantableForm.h"
#include "RE/T/TESFullName.h"
#include "RE/T/TESHealthForm.h"
#include "RE/T/TESIcon.h"
#include "RE/T/TESMagicTargetForm.h"
#include "RE/T/TESModel.h"
#include "RE/T/TESScriptableForm.h"
#include "RE/T/TESValueForm.h"
#include "RE/T/TESWeightForm.h"

namespace RE
{
	class TESObjectWEAP :
		public TESBoundObject,
		public TESFullName,
		public TESModel,
		public TESIcon,
		public TESScriptableForm,
		public TESEnchantableForm,
		public TESValueForm,
		public TESWeightForm,
		public TESHealthForm,
		public TESAttackDamageForm
	{
	public:
		inline static constexpr auto RTTI = RTTI::TESObjectWEAP;
		inline static constexpr auto VTABLE = VTABLE::TESObjectWEAP;
		inline static constexpr auto FORMTYPE = FormType::Weapon;

		// override (TESForm)
		virtual ~TESObjectWEAP() override;                                                              // 04
		virtual void           InitializeData() override;                                               // 05
		virtual bool           Load(TESFile* a_file) override;                                          // 07
		virtual void           Save() override;                                                         // 09
		virtual std::uint16_t  GetSaveSize(std::uint32_t a_changeFlags) override;                       // 13
		virtual void           SaveGame(std::uint32_t a_changeFlags) override;                          // 14
		virtual void           LoadGame(std::uint32_t a_flags, std::uint32_t a_currentFlags) override;  // 15
		virtual void           InitItem() override;                                                     // 1B
		virtual void           Copy(TESForm* a_srcForm) override;                                       // 2D
		virtual bool           Compare(TESForm* a_copyForm) override;                                   // 2E
		virtual void           FillExportForm(bool a_gameplayOnly) override;                            // 38
		virtual void           UpdateFormValues(const ExportTESForm* a_exportForm) override;            // 39
		virtual ExportTESForm* GetExportForm(bool a_fullLoad) override;                                 // 3A
		virtual bool           HasDifferentFormValues(const ExportTESForm* a_exportForm) override;      // 3B

		// members
		OBJ_WEAP data;  // 118
	};
	static_assert(sizeof(TESObjectWEAP) == 0x128);
}
