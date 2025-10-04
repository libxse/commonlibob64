#pragma once

#include "UE/F/FInputActionValue.h"
#include "UE/F/FInputBindingHandle.h"
#include "UE/T/TWeakObjectPtr.h"

namespace UE
{
	class UInputAction;

	class FEnhancedInputActionValueBinding :
		public FInputBindingHandle
	{
	public:
		FEnhancedInputActionValueBinding() = default;

		FEnhancedInputActionValueBinding(const UInputAction* a_action) :
			m_action(a_action)
		{}

	private:
		TWeakObjectPtr<const UInputAction> m_action;        // 010
		mutable FInputActionValue          m_currentValue;  // 018
	};
	static_assert(sizeof(FEnhancedInputActionValueBinding) == 0x38);
}
