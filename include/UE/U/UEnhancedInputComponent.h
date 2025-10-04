#pragma once

#include "UE/F/FEnhancedInputActionEventBinding.h"
#include "UE/F/FEnhancedInputActionValueBinding.h"
#include "UE/F/FInputDebugKeyBinding.h"
#include "UE/U/UInputComponent.h"

namespace UE
{
	class UEnhancedInputComponent :
		public UInputComponent
	{
	public:
		UE_DEFINE_UOBJECT(UEnhancedInputComponent, UInputComponent, "EnhancedInput", "EnhancedInputComponent");

		// override
		virtual ~UEnhancedInputComponent();  // 000

		// members
		TArray<TUniquePtr<FEnhancedInputActionEventBinding>> enhancedActionEventBindings;  // 128
		TArray<FEnhancedInputActionValueBinding>             enhancedActionValueBindings;  // 138
		TArray<TUniquePtr<FInputDebugKeyBinding>>            debugKeyBindings;             // 148
		bool                                                 shouldFireDelegatesInEditor;  // 158
	};
	static_assert(sizeof(UEnhancedInputComponent) == 0x160);
}
