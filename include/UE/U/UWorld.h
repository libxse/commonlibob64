#pragma once

#include "UE/F/FNetworkNotify.h"
#include "UE/U/UObject.h"
#include "UE/U/UWorldProxy.h"

namespace UE
{
	class UWorld :
		public UObject,
		public FNetworkNotify
	{
	public:
		UE_DEFINE_UOBJECT(UWorld, UObject, "Engine", "World");

		// override
		virtual ~UWorld();  // 00

		static UWorldProxy GetSingleton()
		{
			static REL::Relocation<UWorld**> singleton{ ID::UWorld::GetSingleton };
			return UWorldProxy(*singleton);
		}

		// members
		std::byte unk30[0x8D0];  // 30
	};
	static_assert(sizeof(UWorld) == 0x900);
}
