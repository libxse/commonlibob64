#pragma once

#include "UE/F/FKey.h"
#include "UE/T/TBaseDynamicDelegate.h"
#include "UE/T/TDelegate.h"
#include "UE/T/TSharedPtr.h"

namespace UE
{
	using FInputActionHandlerSignature = TDelegate<void()>;
	using FInputActionHandlerWithKeySignature = TDelegate<void(FKey)>;
	using FInputActionHandlerDynamicSignature = TBaseDynamicDelegate<FNotThreadSafeDelegateMode, FKey>;

	class FInputActionUnifiedDelegate
	{
	public:
		enum class EBoundDelegate : std::uint8_t
		{
			Unbound = 0,
			Delegate = 1,
			DelegateWithKey = 2,
			DynamicDelegate = 3
		};

	private:
		// members
		TSharedPtr<FInputActionHandlerSignature>        m_funcDelegate;                                  // 000
		TSharedPtr<FInputActionHandlerWithKeySignature> m_funcDelegateWithKey;                           // 010
		TSharedPtr<FInputActionHandlerDynamicSignature> m_funcDynamicDelegate;                           // 020
		EBoundDelegate                                  m_boundDelegateType{ EBoundDelegate::Unbound };  // 030
	};
	static_assert(sizeof(FInputActionUnifiedDelegate) == 0x38);
}
