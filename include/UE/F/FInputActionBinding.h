#pragma once

#include "UE/E/EInputEvent.h"
#include "UE/F/FInputActionUnifiedDelegate.h"
#include "UE/F/FInputBinding.h"
#include "UE/F/FName.h"
#include "UE/T/TEnumAsByte.h"

#include "UE/UnrealCore.h"

namespace UE
{
	class FInputActionBinding :
		public FInputBinding
	{
	public:
		FInputActionBinding() = default;

		FInputActionBinding(const FName a_name, const EInputEvent a_event) :
			FInputBinding(), keyEvent(a_event), actionName(a_name)
		{}

		// members
		std::uint8_t                paired: 1 { false };               // 001:0
		TEnumAsByte<EInputEvent>    keyEvent{ EInputEvent::Pressed };  // 002
		FName                       actionName{ EName::None };         // 004
		std::int32_t                handle{ INDEX_NONE };              // 00C
		FInputActionUnifiedDelegate actionDelegate;                    // 010
	};
	static_assert(sizeof(FInputActionBinding) == 0x48);
}
