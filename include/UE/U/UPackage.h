#pragma once

#include "UE/F/FCustomVersionContainer.h"
#include "UE/F/FGuid.h"
#include "UE/F/FPackageFileVersion.h"
#include "UE/F/FPackagePath.h"
#include "UE/U/UObject.h"

namespace UE
{
	class FLinkerLoad;
	class FWorldTileInfo;

	class UPackage :
		public UObject
	{
	public:
		UE_DEFINE_UOBJECT_INTRINSIC(UPackage, UObject, "CoreUObject", "Package", EClassFlags::None, EClassCastFlags::UPackage);

		// members
		std::uint8_t            dirty: 1;               // 28:0
		std::uint8_t            hasBeenFullyLoaded: 1;  // 28:1
		std::uint8_t            canBeImported: 1;       // 28:2
		FGuid                   guid;                   // 2C
		std::uint32_t           packageFlagsPrivate;    // 3C
		std::uint64_t           packageId;              // 40 - FPackageId
		FPackagePath            loadedPath;             // 48
		FPackageFileVersion     linkerPackageVersion;   // 54
		std::int32_t            linkerLicenseeVersion;  // 5C
		FCustomVersionContainer linkerCustomVersion;    // 60
		FLinkerLoad*            linkerLoad;             // 70
		std::uint64_t           fileSize;               // 78
		FName                   fileName;               // 80
		std::uintptr_t          worldTileInfo;          // 88 - TUniquePtr<FWorldTileInfo>
	};
	static_assert(sizeof(UPackage) == 0x90);
}
