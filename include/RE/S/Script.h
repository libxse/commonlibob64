#pragma once

#include "RE/B/BSTList.h"
#include "RE/S/SCRIPT_HEADER.h"
#include "RE/T/TESForm.h"

namespace RE
{
	class ScriptLocals;
	class ScriptVariable;
	class TESObjectREFR;

	struct SCRIPT_PARAMETER;
	struct SCRIPT_REFERENCED_OBJECT;

	class Script :
		public TESForm
	{
	public:
		inline static constexpr auto RTTI = RTTI::Script;
		inline static constexpr auto VTABLE = VTABLE::Script;
		inline static constexpr auto FORMTYPE = FormType::Script;

		// override (TESForm)
		virtual ~Script() override;                       // 04
		virtual void InitializeData() override;           // 05
		virtual void ClearData() override;                // 06
		virtual bool Load(TESFile* a_file) override;      // 07
		virtual void Save() override;                     // 09
		virtual bool SaveEdit(TESFile* a_file) override;  // 0B
		virtual void InitItem() override;                 // 1B

		template <class... Args>
		static bool ParseParameters(const SCRIPT_PARAMETER* a_parameters, const char* a_compiledParams, std::uint32_t& a_offset, TESObjectREFR* a_refObject, TESObjectREFR* a_container, Script* a_script, ScriptLocals* a_scriptLocals, Args... a_args)
		{
			static_assert((std::is_pointer_v<Args> && ...), "arguments must all be pointers");
			using func_t = bool(const SCRIPT_PARAMETER*, const char*, std::uint32_t&, TESObjectREFR*, TESObjectREFR*, Script*, ScriptLocals*, ...);
			static REL::Relocation<func_t> func{ ID::Script::ParseParameters };
			return func(a_parameters, a_compiledParams, a_offset, a_refObject, a_container, a_script, a_scriptLocals, a_args...);
		}

		// members
		SCRIPT_HEADER                           header;                       // 30
		char*                                   text;                         // 48
		char*                                   data;                         // 50
		float                                   profilerTimer;                // 58
		float                                   questScriptDelay;             // 5C
		float                                   questScriptGetSecondsBuffer;  // 60
		BSSimpleList<SCRIPT_REFERENCED_OBJECT*> listRefObjects;               // 68
		BSSimpleList<ScriptVariable*>           listVariables;                // 78
	};
	static_assert(sizeof(Script) == 0x88);
}
