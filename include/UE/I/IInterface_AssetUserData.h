#pragma once

#include "UE/I/IInterface.h"
#include "UE/T/TArray.h"
#include "UE/T/TSubclassOf.h"

namespace UE
{
	class UAssetUserData;

	class IInterface_AssetUserData
	{
	public:
		UE_DEFINE_IINTERFACE(IInterface_AssetUserData, "Engine", "Interface_AssetUserData");

		// add
		virtual ~IInterface_AssetUserData();  // 00

		// add
		virtual void                           AddAssetUserData(UAssetUserData* a_assetUserData);                     // 01
		virtual UAssetUserData*                GetAssetUserDataOfClass(TSubclassOf<UAssetUserData> a_userDataClass);  // 02
		virtual const TArray<UAssetUserData*>* GetAssetUserDataArray() const;                                         // 03
		virtual void                           RemoveUserDataOfClass(TSubclassOf<UAssetUserData> a_userDataClass);    // 04
	};
}
