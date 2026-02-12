#pragma once

#include "RE/B/BSTList.h"
#include "RE/G/GAMEPAD_BUTTON.h"
#include "RE/I/IVPairableItem.h"
#include "RE/M/MENU_CLASS.h"
#include "RE/T/Tile.h"

namespace RE
{
	class TileMenu;

	class Menu :
		public IVPairableItem
	{
	public:
		inline static constexpr auto RTTI = RTTI::Menu;
		inline static constexpr auto VTABLE = VTABLE::Menu;

		enum class FADE_STATE : std::int32_t
		{
			kFADE_SHOWN = 0x1,
			kFADING_OUT = 0x2,
			kFADE_HIDDEN = 0x4,
			kFADING_IN = 0x8,
			kFADE_ALL = 0xF,
			kFADE_IN_SHOWN = 0x9,
			kFADE_OUT_SHOWN = 0x3,
			kFADE_NOT_HIDDEN = 0xB,
		};

		virtual ~Menu();  // 07

		// add
		virtual void         AttachTileByID(std::int32_t a_ID, Tile* a_tile);    // 08
		virtual void         DoDownClick(std::int32_t a_ID, Tile* a_target);     // 09
		virtual void         DoClick(std::int32_t a_ID, Tile* a_target);         // 0A
		virtual void         DoEnter(std::int32_t a_ID, Tile* a_target);         // 0B
		virtual void         DoLeave(std::int32_t a_ID, Tile* a_target);         // 0C
		virtual void         DoDragEnter(std::int32_t, Tile*, Tile*);            // 0D
		virtual void         DoDragLeave(std::int32_t, Tile*, Tile*);            // 0E
		virtual void         DoStillDown(std::int32_t a_ID, Tile* a_target);     // 0F
		virtual void         DoStillDragOver(std::int32_t, Tile*);               // 10
		virtual void         DoWheelMove(std::int32_t a_ID, Tile* a_target);     // 11
		virtual void         DoIdle();                                           // 12
		virtual bool         DoKey(std::int32_t a_key);                          // 13
		virtual std::int32_t GetClass();                                         // 14
		virtual bool         DoGamepad(GAMEPAD_BUTTON a_button, float a_value);  // 15
		virtual void         StartFadeOut();                                     // 16
		virtual void         CancelFadeOut();                                    // 17
		virtual void         StartFadeIn();                                      // 18

		// members
		TileMenu*                            tileMenu;         // 18
		BSSimpleList<Tile::TileTemplate*>    templates;        // 20
		Tile*                                lastTile;         // 30
		std::int32_t                         isModal;          // 38
		std::int32_t                         menuThickness;    // 3C
		bool                                 forceFadeOut;     // 40
		bool                                 deleteTemplates;  // 41
		REX::TEnum<MENU_CLASS, std::int32_t> menuClass;        // 44
		REX::TEnum<FADE_STATE, std::int32_t> fadeState;        // 48
	};
	static_assert(sizeof(Menu) == 0x50);
}
