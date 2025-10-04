#pragma once

#include "UE/F/FName.h"
#include "UE/F/FWeakObjectPtr.h"
#include "UE/T/TDelegateAccessHandlerBase.h"

namespace UE::Core::Private
{
	template <class M>
	struct TScriptDelegateTraits
	{
		using WeakPtrType = FWeakObjectPtr;
		using ThreadSafetyMode = M;
		using UnicastThreadSafetyModeForMulticasts = FNotThreadSafeNotCheckedDelegateMode;
	};
}

namespace UE
{
	template <class M = FNotThreadSafeDelegateMode>
	class TScriptDelegate :
		public TDelegateAccessHandlerBase<typename Core::Private::TScriptDelegateTraits<M>::ThreadSafetyMode>
	{
	public:
		using WeakPtrType = Core::Private::TScriptDelegateTraits<M>::WeakPtrType;

		// members
		WeakPtrType object;
		FName       functionName;
	};
}
