#pragma once

#include "UE/T/TArray.h"

namespace UE
{
	class FWeatherEntry;

	class FTESWeatherList
	{
	public:
		// members
		TArray<FWeatherEntry> weatherEntries;
	};
	static_assert(sizeof(FTESWeatherList) == 0x10);
}
