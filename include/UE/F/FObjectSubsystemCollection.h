#pragma once

#include "UE/T/TMap.h"
#include "UE/T/TObjectPtr.h"

namespace UE
{
	class UClass;
	class UObject;
	class USubsystem;

	class FSubsystemCollectionBase
	{
	public:
		// add
		virtual ~FSubsystemCollectionBase();  // 00

		// members
		TMap<TObjectPtr<UClass>, TObjectPtr<USubsystem>> subsystemMap;       // 008
		mutable TMap<UClass*, TArray<USubsystem*>>       subsystemArrayMap;  // 058
		UClass*                                          baseType;           // 0A8
		UObject*                                         outer;              // 0B0
		bool                                             populating;         // 0B8
	};
	static_assert(sizeof(FSubsystemCollectionBase) == 0xC0);

	template <class T>
	class FObjectSubsystemCollection :
		public FSubsystemCollectionBase
	{
	public:

	};
}
