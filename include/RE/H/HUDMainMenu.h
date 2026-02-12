#pragma once

#include "RE/I/IconArray.h"
#include "RE/M/Menu.h"

namespace RE
{
	class TESQuestTarget;
	class Tile;

	class HUDMainMenu :
		public Menu
	{
	public:
		inline static constexpr auto RTTI = RTTI::HUDMainMenu;
		inline static constexpr auto VTABLE = VTABLE::HUDMainMenu;

		enum class MENU_POSITION : std::int32_t
		{
			kMENU_POSITION_NONE = -1,
			kMENU_POSITION_A = 0,
			kMENU_POSITION_B = 1,
			kMENU_POSITION_C = 2,
			kMENU_POSITION_D = 3,
			kMENU_POSITION_COUNT = 4,
		};

		virtual ~HUDMainMenu() override;  // 07

		// override (IVPairableItem)
		virtual void ProcessPairItem() override;    // 01
		virtual void ProcessUnpairItem() override;  // 02

		// override (Menu)
		virtual void         AttachTileByID(std::int32_t a_ID, Tile* a_tile) override;  // 08
		virtual void         DoDownClick(std::int32_t a_ID, Tile* a_target) override;   // 09
		virtual void         DoClick(std::int32_t a_ID, Tile* a_target) override;       // 0A
		virtual void         DoStillDown(std::int32_t a_ID, Tile* a_target) override;   // 0F
		virtual void         DoIdle() override;                                         // 12
		virtual std::int32_t GetClass() override;                                       // 14
		virtual void         StartFadeOut() override;                                   // 16
		virtual void         StartFadeIn() override;                                    // 18

		// members
		Tile*                                   background;         // 050
		Tile*                                   health;             // 058
		Tile*                                   magic;              // 060
		Tile*                                   fatigue;            // 068
		Tile*                                   weapon;             // 070
		Tile*                                   spell;              // 078
		Tile*                                   compass;            // 080
		Tile*                                   compassFace;        // 088
		Tile*                                   frame;              // 090
		Tile*                                   playerGrab;         // 098
		Tile*                                   activeFXIcons;      // 0A0
		Tile*                                   levelupIcon;        // 0A8
		Tile*                                   brackets;           // 0B0
		REX::TEnum<MENU_POSITION, std::int32_t> currentLoc;         // 0B8
		REX::TEnum<MENU_POSITION, std::int32_t> destLoc;            // 0BC
		BSSimpleList<TESQuestTarget*>*          questList;          // 0C0
		float                                   mouseDownX;         // 0C8
		float                                   mouseDownY;         // 0CC
		float                                   zoomPos;            // 0D0
		std::uint32_t                           killRegionDisplay;  // 0D4
		IconArray                               activeFX;           // 0D8
		bool                                    isVisible;          // 100
	};
	static_assert(sizeof(HUDMainMenu) == 0x108);
}
