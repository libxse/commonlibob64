#pragma once

namespace UE
{
	enum class ESpawnActorScaleMethod : std::uint8_t
	{
		OverrideRootScale,
		MultiplyWithRoot,
		SelectDefaultAtRuntime,
	};
}
