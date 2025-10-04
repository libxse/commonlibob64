#pragma once

namespace UE
{
	enum class ETriggerEvent : std::uint8_t
	{
		None = 0,
		Triggered = 1 << 0,
		Started = 1 << 1,
		Ongoing = 1 << 2,
		Canceled = 1 << 3,
		Completed = 1 << 4
	};
	REX_DEFINE_ENUM_CLASS_FLAGS(ETriggerEvent);
}
