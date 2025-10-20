#pragma once

#include "RE/S/Setting.h"
#include "RE/S/SettingCollectionMap.h"

namespace RE
{
	class TESFile;

	class GameSettingCollection :
		public SettingCollectionMap<Setting>
	{
	public:
		inline static constexpr auto RTTI = RTTI::GameSettingCollection;
		inline static constexpr auto VTABLE = VTABLE::GameSettingCollection;

		~GameSettingCollection() override;  // 00

		// override
		virtual std::uint32_t GetViewerStrings(NiTArray<char*>* a_strings) override;  // 03
		virtual bool          ReadSetting(Setting& a_setting) override;               // 05

		// add
		virtual bool ReadSetting(TESFile* a_file, const char* a_key);  // 0A

		static GameSettingCollection* GetSingleton()
		{
			static REL::Relocation<GameSettingCollection*> singleton{ ID::GameSettingCollection::Singleton };
			return singleton.get();
		}

		Setting* GetSetting(const char* a_name)
		{
			auto it = settings.find(a_name);
			return it != settings.end() ? it->second : nullptr;
		}
	};
	static_assert(sizeof(GameSettingCollection) == 0x140);
}
