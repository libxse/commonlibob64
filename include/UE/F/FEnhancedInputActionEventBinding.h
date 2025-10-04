#pragma once

#include "UE/E/ETriggerEvent.h"
#include "UE/F/FInputBindingHandle.h"
#include "UE/T/TUniquePtr.h"
#include "UE/T/TWeakObjectPtr.h"

namespace UE
{
	class FInputActionInstance;
	class UInputAction;

	class FEnhancedInputActionEventBinding :
		public FInputBindingHandle
	{
	public:
		FEnhancedInputActionEventBinding() = default;

		FEnhancedInputActionEventBinding(const UInputAction* a_action, ETriggerEvent a_event) :
			m_action(a_action), m_event(a_event)
		{}

		// add
		virtual void                                         Execute(const FInputActionInstance& a_data) const = 0;       // 001
		virtual TUniquePtr<FEnhancedInputActionEventBinding> Clone() const = 0;                                           // 002
		virtual void                                         SetShouldFireWithEditorScriptGuard(const bool a_value) = 0;  // 003
		virtual bool                                         IsBoundToObject(const void* a_object) const = 0;             // 004

	private:
		TWeakObjectPtr<const UInputAction> m_action;                        //
		ETriggerEvent                      m_event{ ETriggerEvent::None };  //
	};
	static_assert(sizeof(FEnhancedInputActionEventBinding) == 0x20);
}
