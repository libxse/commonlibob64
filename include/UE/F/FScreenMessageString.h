#pragma once

#include "UE/F/FColor.h"
#include "UE/F/FString.h"
#include "UE/F/FVector2.h"

namespace UE
{
	class FScreenMessageString
	{
	public:
		// members
		std::uint64_t key{ 0 };                   // 000
		FString       screenMessage;              // 008
		FColor        displayColor;               // 018
		float         timeToDisplay{ 0 };         // 01C
		float         currentTimeDisplayed{ 0 };  // 020
		FVector2D     textScale;                  // 028
	};
	static_assert(sizeof(FScreenMessageString) == 0x38);
}
