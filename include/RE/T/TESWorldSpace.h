#pragma once

#include "RE/B/BSStringT.h"
#include "RE/B/BSTList.h"
#include "RE/C/CELL_MUSIC_TYPE.h"
#include "RE/N/NiPoint2.h"
#include "RE/N/NiTPointerMap.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESFullName.h"
#include "RE/T/TESTerrainLODManager.h"
#include "RE/T/TESTexture.h"
#include "RE/W/WORLD_MAP_DATA.h"

namespace RE
{
	class TESClimate;
	class TESGrassAreaParam;
	class TESObjectCELL;
	class TESRoad;
	class TESWaterForm;

	class TESWorldSpace :
		public TESForm,
		public TESFullName,
		public TESTexture
	{
	public:
		inline static constexpr auto RTTI = RTTI::TESWorldSpace;
		inline static constexpr auto VTABLE = VTABLE::TESWorldSpace;
		inline static constexpr auto FORMTYPE = FormType::WorldSpace;

		// override (TESForm)
		virtual ~TESWorldSpace() override;                                                                                      // 04
		virtual void        InitializeData() override;                                                                          // 05
		virtual void        ClearData() override;                                                                               // 06
		virtual bool        Load(TESFile* a_file) override;                                                                     // 07
		virtual void        Save() override;                                                                                    // 09
		virtual bool        SavesBefore(FORM* a_group) override;                                                                // 0C
		virtual bool        SavesBefore(TESForm* a_form) override;                                                              // 0D
		virtual TESForm*    CreateDuplicateForm(bool a_createEditorID, NiTPointerMap<TESForm*, TESForm*>* a_copyMap) override;  // 0E
		virtual bool        FindInFileFast(TESFile* a_file) override;                                                           // 1A
		virtual void        InitItem() override;                                                                                // 1B
		virtual void        Copy(TESForm* a_srcForm) override;                                                                  // 2D
		virtual bool        Compare(TESForm* a_copyForm) override;                                                              // 2E
		virtual bool        IsFormTypeChild(FormType a_type) override;                                                          // 32
		virtual const char* GetFormEditorID() override;                                                                         // 35
		virtual bool        SetFormEditorID(const char* a_editorID) override;                                                   // 36

		// add
		virtual bool GetMapNameForLocation(BSString& a_mapName, NiPoint3 a_worldLocation);                                                                                   // 3C
		virtual void GetGrassForLocation(NiPoint2 a_minWorldLocation, NiPoint2 a_maxWorldLocation, const TESGrassAreaParam* a_grassParams, std::uint32_t a_numGrassParams);  // 3D

		// members
		NiTPointerMap<std::int32_t, TESObjectCELL*>*                 cellMap;                  // 060
		TESObjectCELL*                                               persistentCell;           // 068
		TESTerrainLODManager                                         terrainLODManager;        // 070
		TESRoad*                                                     road;                     // 0A8
		TESClimate*                                                  climate;                  // 0B0
		std::uint8_t                                                 flags;                    // 0B8
		NiTPointerMap<std::uint32_t, BSSimpleList<TESObjectREFR*>*>* subSpaceMap;              // 0C0
		NiTPointerMap<std::uint32_t, BSSimpleList<TESObjectREFR*>*>  fixedPersistentRefMap;    // 0C8
		BSSimpleList<TESObjectREFR*>                                 mobilePersistentRefList;  // 0E8
		TESWorldSpace*                                               parentWorld;              // 0F8
		TESWaterForm*                                                worldWater;               // 100
		WORLD_MAP_DATA                                               worldMapData;             // 108
		CELL_MUSIC_TYPE                                              musicType;                // 118
		NiPoint2                                                     minimumCoords;            // 11C
		NiPoint2                                                     maximumCoords;            // 124
		std::uint32_t*                                               cellFileOffsets;          // 130
		NiPoint2                                                     offsetMinCoords;          // 138
		NiPoint2                                                     offsetMaxCoords;          // 140
		std::uint32_t                                                fileOffset;               // 148
		BSString                                                     editorID;                 // 150
		NiTPointerMap<std::uint32_t, bool>                           cellsWithLODObjects;      // 160
		bool                                                         foundLODObjectsFile;      // 180
		std::int32_t                                                 distantLODFlags;          // 184
	};
	static_assert(sizeof(TESWorldSpace) == 0x188);
}
