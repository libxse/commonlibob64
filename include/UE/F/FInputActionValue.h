#pragma once

#include "UE/E/EInputActionValueType.h"
#include "UE/F/FVector.h"

namespace UE
{
	class FInputActionValue
	{
	public:
		FInputActionValue() = default;

	private:
		FVector               m_value{ 0.0, 0.0, 0.0 };                       // 000
		EInputActionValueType m_valueType{ EInputActionValueType::Boolean };  // 018
	};
	static_assert(sizeof(FInputActionValue) == 0x20);
}
