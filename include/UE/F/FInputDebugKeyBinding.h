#pragma once

#include "UE/E/EInputEvent.h"
#include "UE/F/FInputBindingHandle.h"
#include "UE/F/FInputChord.h"
#include "UE/T/TEnumAsByte.h"
#include "UE/T/TUniquePtr.h"

namespace UE
{
	class FInputActionValue;

	class FInputDebugKeyBinding :
		public FInputBindingHandle
	{
	public:
		FInputDebugKeyBinding() = default;

		// add
		virtual void                              Execute(const FInputActionValue& a_value) const = 0;  // 001
		virtual TUniquePtr<FInputDebugKeyBinding> Clone() const = 0;                                    // 002

	private:
		TEnumAsByte<EInputEvent> m_event;              // 010
		bool                     m_executeWhenPaused;  // 011
		FInputChord              m_chord;              // 018
	};
	static_assert(sizeof(FInputDebugKeyBinding) == 0x38);
}
