#pragma once

#include "UE/E/EInputEvent.h"
#include "UE/F/FInputActionBinding.h"
#include "UE/T/TSharedPtr.h"
#include "UE/U/UActorComponent.h"

namespace UE
{
	class FCachedKeyToActionInfo;
	class FInputActionBinding;
	class FInputAxisBinding;
	class FInputAxisKeyBinding;
	class FInputGestureBinding;
	class FInputKeyBinding;
	class FInputTouchBinding;
	class FInputVectorAxisBinding;

	class UInputComponent :
		public UActorComponent
	{
	public:
		UE_DEFINE_UOBJECT(UInputComponent, UActorComponent, "Engine", "InputComponent");

		// override
		virtual ~UInputComponent();  // 000

		// add
		virtual void ClearBindingsForObject(UObject* a_owner);  // 093
		virtual void ClearActionBindings();                     // 094

		FInputActionBinding& AddActionBinding(FInputActionBinding a_binding)
		{
			using func_t = decltype(&UInputComponent::AddActionBinding);
			static REL::Relocation<func_t> func{ ID::UInputComponent::AddActionBinding };
			return func(this, a_binding);
		}

		// members
		TArray<FInputKeyBinding>                keyBindings;            // 0A0
		TArray<FInputTouchBinding>              touchBindings;          // 0B0
		TArray<FInputAxisBinding>               axisBindings;           // 0C0
		TArray<FInputAxisKeyBinding>            axisKeyBindings;        // 0D0
		TArray<FInputVectorAxisBinding>         vectorAxisBindings;     // 0E0
		TArray<FInputGestureBinding>            gestureBindings;        // 0F0
		TArray<TSharedPtr<FInputActionBinding>> actionBindings;         // 100
		TArray<FCachedKeyToActionInfo>          cachedKeyToActionInfo;  // 110
		std::int32_t                            priority;               // 120
		std::uint8_t                            blockInput: 1;          // 124:0
	};
	static_assert(sizeof(UInputComponent) == 0x128);
}
