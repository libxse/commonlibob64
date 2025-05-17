#pragma once

#include "UE/F/FString.h"
#include "UE/F/FTopLevelAssetPath.h"

namespace UE
{
	class FSoftObjectPath
	{
	public:
		FSoftObjectPath() = default;

		// members
		FTopLevelAssetPath assetPath;      // 00
		FString            subPathString;  // 10
	};
	static_assert(sizeof(FSoftObjectPath) == 0x20);
}
