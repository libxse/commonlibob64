#pragma once

namespace UE
{
	enum class EAsyncExecution : std::int32_t
	{
		TaskGraph = 0,
		TaskGraphMainThread = 1,
		Thread = 2,
		ThreadIfForkSafe = 3,
		ThreadPool = 4,
	};
}
