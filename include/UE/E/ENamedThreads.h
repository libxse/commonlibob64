#pragma once

namespace UE
{
	enum class ENamedThreads : std::int32_t
	{
		RHIThread = 0,
		GameThread = 1,
		ActualRenderingThread = 2,
		AnyThread = 255, 
	};
}
