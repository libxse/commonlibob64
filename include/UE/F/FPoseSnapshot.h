#pragma once

#include "UE/F/FName.h"
#include "UE/F/FTransform.h"
#include "UE/T/TArray.h"
#include "UE/T/TTransform.h"

namespace UE
{
	class FPoseSnapshot
	{
	public:
		// members
		TArray<FTransform> localTransforms;   // 000
		TArray<FName>      boneNames;         // 010
		FName              skeletalMeshName;  // 020
		FName              snapshotName;      // 028
		bool               isValid;           // 030
	};
	static_assert(sizeof(FPoseSnapshot) == 0x038);
}
