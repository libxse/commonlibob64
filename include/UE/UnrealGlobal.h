#pragma once

#include "UE/E/ENamedThreads.h"
#include "UE/T/TUniqueFunction.h"

namespace UE
{
	inline bool AsyncTask(ENamedThreads a_thread, TUniqueFunction<void()> a_function)
	{
		using func_t = decltype(&AsyncTask);
		static REL::Relocation<func_t> func{ ID::AsyncTask };
		return func(a_thread, std::move(a_function));
	}

	inline bool IsInGameThread()
	{
		using func_t = decltype(&IsInGameThread);
		static REL::Relocation<func_t> func{ ID::IsInGameThread };
		return func();
	}
}
