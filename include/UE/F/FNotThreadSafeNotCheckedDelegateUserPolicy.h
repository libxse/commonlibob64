#pragma once

#include "UE/F/FDefaultDelegateUserPolicy.h"
#include "UE/I/IDelegateInstance.h"
#include "UE/T/TMulticastDelegateBase.h"

namespace UE
{
	struct FNotThreadSafeNotCheckedDelegateMode;

	struct FNotThreadSafeNotCheckedDelegateUserPolicy
	{
		using FThreadSafetyMode = FNotThreadSafeNotCheckedDelegateMode;
		using FDelegateExtras = TDelegateBase<FThreadSafetyMode>;
		using FDelegateInstanceExtras = IDelegateInstance;
		using FMulticastDelegateExtras = TMulticastDelegateBase<FDefaultDelegateUserPolicy>;
	};
}
