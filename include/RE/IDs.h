#pragma once

namespace RE::ID
{
	namespace Actor
	{
		inline constexpr REL::ID EquipObject{ 405993 };
		inline constexpr REL::ID GetItemCountInContainer{ 406091 };
		inline constexpr REL::ID GetLevel{ 406093 };
		inline constexpr REL::ID UnequipObject{ 406356 };
	}

	namespace BaseExtraList
	{
		inline constexpr REL::ID AddExtra{ 407178 };
		inline constexpr REL::ID GetExtraData{ 407219 };
		inline constexpr REL::ID ItemsInList{ 407290 };
		inline constexpr REL::ID RemoveAll{ 407293 };
		inline constexpr REL::ID RemoveExtra{ 407306 };
	}

	namespace Calendar
	{
		inline constexpr REL::ID Singleton{ 1669511 };
	}

	namespace FORM_ENUM_STRING
	{
		inline constexpr REL::ID FormEnumString{ 1462745 };
	}

	namespace GameSettingCollection
	{
		inline constexpr REL::ID Singleton{ 1464798 };
	}

	namespace INISettingCollection
	{
		inline constexpr REL::ID Singleton{ 1464496 };
	}

	namespace InterfaceManager
	{
		inline constexpr REL::ID GetInstance{ 406444 };
	}

	namespace MapMenu
	{
		inline constexpr REL::ID CenterMapAt{ 404937 };
		inline constexpr REL::ID SwitchTabs{ 404990 };
		inline constexpr REL::ID SwitchTabsNotifyingAltar{ 404991 };
		inline constexpr REL::ID Update{ 404992 };
	}

	namespace MenuConsole
	{
		inline constexpr REL::ID Instance{ 407549 };
		inline constexpr REL::ID PrintLine{ 407552 };
	}

	namespace PlayerCharacter
	{
		inline constexpr REL::ID Singleton{ 1667589 };
	}

	namespace Script
	{
		inline constexpr REL::ID ParseParameters{ 407526 };
	}

	namespace SCRIPT_FUNCTION
	{
		inline constexpr REL::ID ConsoleFunctions{ 1471272 };
		inline constexpr REL::ID ScriptFunctions{ 1469048 };
	}

	namespace Setting
	{
		inline constexpr REL::ID SetString{ 409216 };
	}

	namespace TESDataHandler
	{
		inline constexpr REL::ID Singleton{ 1667969 };
	}

	namespace TESFile
	{
		inline constexpr REL::ID CloseTES{ 411591 };
		inline constexpr REL::ID GetTESChunk{ 411609 };
		inline constexpr REL::ID GetChunkData{ 411601 };
		inline constexpr REL::ID NextChunk{ 411618 };
		inline constexpr REL::ID NextForm{ 411619 };
		inline constexpr REL::ID OpenTES{ 411622 };
	}

	namespace TESForm
	{
		inline constexpr REL::ID AllForms{ 1462827 };
		inline constexpr REL::ID AllFormsByEditorID{ 1462835 };
	}

	namespace TESFullName
	{
		inline constexpr REL::ID GetFullName{ 405447 };
	}

	namespace TESObjectREFR
	{
		inline constexpr REL::ID GetInterior{ 405453 };
		inline constexpr REL::ID GetWorldSpace{ 405508 };
	}

	namespace Tile
	{
		inline constexpr REL::ID GetMenuByClass{ 409363 };
		inline constexpr REL::ID GetMenu{ 409362 };
	}

	inline constexpr REL::ID RTDynamicCast{ 427658 };
}

namespace UE::ID
{
	namespace FFrame
	{
		inline constexpr REL::ID KismetExecutionMessage{ 116737 };
	}

	namespace FLogScopedCategoryAndVerbosityOverride
	{
		inline constexpr REL::ID GetTLSCurrent{ 110003 };
	}

	namespace FMemory
	{
		inline constexpr REL::ID Free{ 108444 };
		inline constexpr REL::ID Malloc{ 108612 };
		inline constexpr REL::ID Realloc{ 108654 };
		inline constexpr REL::ID QuantizeSize{ 108646 };
	}

	namespace FName
	{
		inline constexpr REL::ID Ctor1{ 112049 };
		inline constexpr REL::ID Ctor2{ 112051 };
		inline constexpr REL::ID AppendString{ 112087 };
		inline constexpr REL::ID ToString{ 112307 };
	}

	namespace FNamePool
	{
		inline constexpr REL::ID GetSingleton{ 1478297 };
	}

	namespace FParse
	{
		inline constexpr REL::ID Command{ 111232 };
	}

	namespace FSelfRegisteringExec
	{
		inline constexpr REL::ID Ctor{ 110681 };
		inline constexpr REL::ID Dtor{ 110692 };
	}

	namespace FString
	{
		inline constexpr REL::ID AppendChar{ 107257 };
		inline constexpr REL::ID AppendChars1{ 107258 };
		inline constexpr REL::ID AppendChars2{ 107259 };
		inline constexpr REL::ID Ctor1{ 107217 };
		inline constexpr REL::ID Ctor2{ 107218 };
		inline constexpr REL::ID Reset{ 107404 };
	}

	namespace FText
	{
		inline constexpr REL::ID Ctor1{ 108973 };
		inline constexpr REL::ID GetEmpty{ 109368 };
		inline constexpr REL::ID Rebuild{ 109545 };
	}

	namespace FUObjectArray
	{
		inline constexpr REL::ID GetSingleton{ 1479488 };
	}

	namespace UAltarCheatManager
	{
		inline constexpr REL::ID GetSelectedActor{ 197301 };
		inline constexpr REL::ID SetSelectedActor{ 304600 };
	}

	namespace UClass
	{
		inline constexpr REL::ID FindFunctionByName{ 114200 };
	}

	namespace UEngine
	{
		inline constexpr REL::ID GetSingleton{ 1583525 };
		inline constexpr REL::ID GetCurrentPlayWorld{ 241719 };
	}

	namespace UGameplayStatics
	{
		inline constexpr REL::ID GetPlayerController{ 220839 };
	}

	namespace UObjectBaseUtility
	{
		inline constexpr REL::ID GetFullName1{ 117106 };
		inline constexpr REL::ID GetFullName2{ 117108 };
	}

	namespace UWorld
	{
		inline constexpr REL::ID GetSingleton{ 1584597 };
	}

	namespace VOblivionUEPairingGate
	{
		inline constexpr REL::ID GetSingleton{ 286331 };
	}

	inline constexpr REL::ID AsyncTask{ 106836 };
	inline constexpr REL::ID GetExecRegistry{ 110855 };
	inline constexpr REL::ID GetExecRegistryLock{ 110856 };
	inline constexpr REL::ID GetTransientPackage{ 115232 };
	inline constexpr REL::ID IsInGameThread{ 108577 };
	inline constexpr REL::ID LowLevelFatalErrorHandler{ 110499 };
	inline constexpr REL::ID StaticConstructObject_Internal{ 117210 };
	inline constexpr REL::ID StaticFindObjectFast{ 117220 };
	inline constexpr REL::ID StaticFindObjectFastSafe{ 117223 };
	inline constexpr REL::ID StaticFindObject{ 117217 };
	inline constexpr REL::ID StaticFindObjectSafe{ 117224 };
}
