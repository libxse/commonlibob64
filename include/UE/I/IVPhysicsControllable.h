#pragma once

#include "UE/I/IInterface.h"
#include "UE/T/TDelegate.h"
#include "UE/T/TTransform.h"

namespace UE
{
	class IVPhysicsControllable
	{
	public:
		UE_DEFINE_IINTERFACE(IVPhysicsControllable, "Altar", "VPhysicsControllable");

		// add
		virtual ~IVPhysicsControllable();  // 00

		// members
		bool                               isDebugTarget;                            // 008
		bool                               shouldLoadPhysicsStateOnSimulationStart;  // 009
		TDelegate<void(const FTransform&)> onPostEnvironmentSnapDelegate;            // 010
	};
	static_assert(sizeof(IVPhysicsControllable) == 0x020);
}
