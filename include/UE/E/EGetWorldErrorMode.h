#pragma once

namespace UE
{
	enum class EGetWorldErrorMode : std::int32_t
	{
		ReturnNull = 0,
		LogAndReturnNull = 1,
		Assert = 2
	};
}
