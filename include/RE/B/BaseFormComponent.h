#pragma once

#include "RE/M/MemoryManager.h"

namespace RE
{
	class BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI::BaseFormComponent;

		virtual void InitializeDataComponent();                   // 00
		virtual void ClearDataComponent();                        // 01
		virtual void CopyComponent(BaseFormComponent* a_rhs);     // 02
		virtual bool CompareComponent(BaseFormComponent* a_rhs);  // 03

		TES4_DEFINE_NEW();
	};
	static_assert(sizeof(BaseFormComponent) == 0x8);
}
