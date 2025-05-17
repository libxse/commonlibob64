#pragma once

#include "UE/I/IInterface.h"
#include "UE/T/TWeakObjectPtr.h"

namespace UE
{
	class UObject;
	class UVFreezeInMenuSubsystem;

	class IReactToFreezeInterface
	{
	public:
		UE_DEFINE_IINTERFACE(IReactToFreezeInterface, "Altar", "ReactToFreezeInterface");

		// add
		virtual ~IReactToFreezeInterface();  // 00

		// add
		virtual UObject* _GetUObject();                // 01
		virtual void     OnFreezeUnfreezeEvent(bool);  // 02
		virtual void     OnFreezeTick(float);          // 03

		// members
		TWeakObjectPtr<UVFreezeInMenuSubsystem> relatedFreezeSubsystemInstance;
		bool                                    isFrozen;
	};
	static_assert(sizeof(IReactToFreezeInterface) == 0x018);
}
