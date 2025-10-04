#pragma once

namespace UE
{
	enum class EInputEvent : std::int32_t
	{
		Pressed = 0,
		Released = 1,
		Repeat = 2,
		DoubleClick = 3,
		Axis = 4,
	};
}
