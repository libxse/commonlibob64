#pragma once

namespace UE
{
	enum class EActorUpdateOverlapsMethod : std::uint8_t
	{
		UseConfigDefault,
		AlwaysUpdate,
		OnlyUpdateMovable,
		NeverUpdate
	};
}
