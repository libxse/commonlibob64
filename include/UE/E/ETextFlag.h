#pragma once

namespace UE
{
	enum class ETextFlag : std::int32_t
	{
		Transient = 1 << 0,
		CultureInvariant = 1 << 1,
		ConvertedProperty = 1 << 2,
		Immutable = 1 << 3,
		InitializedFromString = 1 << 4,
	};
	REX_DEFINE_ENUM_CLASS_FLAGS(ETextFlag);
}
