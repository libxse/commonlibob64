#pragma once

namespace RE::ID
{
	namespace FORM_ENUM_STRING
	{
		inline constexpr REL::Offset FormEnumString{ 0x8FDD6A0 };
	}

	namespace GameSettingCollection
	{
		inline constexpr REL::Offset Singleton{ 0x8FE1E10 };
	}

	namespace MenuConsole
	{
		inline constexpr REL::Offset Instance{ 0x665C360 };
		inline constexpr REL::Offset PrintLine{ 0x665C580 };
	}

	namespace PlayerCharacter
	{
		inline constexpr REL::Offset Singleton{ 0x9455388 };
	}

	namespace SCRIPT_FUNCTION
	{
		inline constexpr REL::Offset ConsoleFunctions{ 0x8FF3C40 };
		inline constexpr REL::Offset ScriptFunctions{ 0x8FEC850 };
	}

	namespace Setting
	{
		inline constexpr REL::Offset SetString{ 0x6710B70 };
	}

	namespace TESDataHandler
	{
		inline constexpr REL::Offset Singleton{ 0x94B5C98 };
	}

	namespace TESForm
	{
		inline constexpr REL::Offset AllForms{ 0x8FDDD30 };
		inline constexpr REL::Offset AllFormsByEditorID{ 0x8FDDD70 };
	}

	namespace TESObjectREFR
	{
		inline constexpr REL::Offset GetInterior{ 0x65A8400 };
	}

	namespace Tile
	{
		inline constexpr REL::Offset GetMenuByClass{ 0x671B0C0 };
		inline constexpr REL::Offset GetMenu{ 0x671B070 };
	}

	inline constexpr REL::Offset RTDynamicCast{ 0x6C23656 };
}

namespace UE::ID
{
	namespace FFrame
	{
		inline constexpr REL::Offset KismetExecutionMessage{ 0x10FD030 };
	}

	namespace FMemory
	{
		inline constexpr REL::Offset Free{ 0x0E30580 };
		inline constexpr REL::Offset Malloc{ 0x0E3CFC0 };
		inline constexpr REL::Offset Realloc{ 0x0E3EE30 };
		inline constexpr REL::Offset QuantizeSize{ 0x0E3E800 };
	}

	namespace FName
	{
		inline constexpr REL::Offset Ctor1{ 0x0F45900 };
		inline constexpr REL::Offset Ctor2{ 0x0F45A70 };
		inline constexpr REL::Offset AppendString{ 0x0F4B710 };
		inline constexpr REL::Offset ToString{ 0x0F61010 };
	}

	namespace FNamePool
	{
		inline constexpr REL::Offset GetSingleton{ 0x909EE80 };
	}

	namespace FString
	{
		inline constexpr REL::Offset Ctor1{ 0x0DE4F20 };
		inline constexpr REL::Offset Ctor2{ 0x0DE50B0 };
	}

	namespace FText
	{
		inline constexpr REL::Offset Ctor1{ 0x0E561F0 };
		inline constexpr REL::Offset GetEmpty{ 0x0E6E7C0 };
		inline constexpr REL::Offset Rebuild{ 0x0E7F220 };
	}

	namespace FUObjectArray
	{
		inline constexpr REL::Offset GetSingleton{ 0x9145160 };
	}

	namespace UClass
	{
		inline constexpr REL::Offset FindFunctionByName{ 0x1005AA0 };
	}

	namespace UEngine
	{
		inline constexpr REL::Offset GetSingleton{ 0x92B0E48 };
		inline constexpr REL::Offset GetCurrentPlayWorld{ 0x37F0A20 };
	}

	namespace UGameplayStatics
	{
		inline constexpr REL::Offset GetPlayerController{ 0x31B6B80 };
	}

	namespace UObjectBaseUtility
	{
		inline constexpr REL::Offset GetFullName1{ 0x111F730 };
		inline constexpr REL::Offset GetFullName2{ 0x111F8D0 };
	}

	namespace UWorld
	{
		inline constexpr REL::Offset GetSingleton{ 0x92B3878 };
	}

	inline constexpr REL::Offset AsyncTask{ 0x0DC48F0 };
	inline constexpr REL::Offset GetTransientPackage{ 0x109A510 };
	inline constexpr REL::Offset IsInGameThread{ 0x0E3C380 };
	inline constexpr REL::Offset LowLevelFatalErrorHandler{ 0x0ED7980 };
	inline constexpr REL::Offset StaticConstructObject_Internal{ 0x1129D30 };
	inline constexpr REL::Offset StaticFindObjectFast{ 0x112C350 };
	inline constexpr REL::Offset StaticFindObjectFastSafe{ 0x112CC40 };
	inline constexpr REL::Offset StaticFindObject{ 0x112C0F0 };
	inline constexpr REL::Offset StaticFindObjectSafe{ 0x112CCE0 };
}
