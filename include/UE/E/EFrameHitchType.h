#pragma once

namespace UE
{
	enum class EFrameHitchType : std::uint8_t
	{
		NoHitch = 0,
		UnknownUnit = 1,
		GameThread = 2,
		RenderThread = 3,
		RHIThread = 4,
		GPU = 5
	};
}
