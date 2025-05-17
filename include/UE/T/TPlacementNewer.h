#pragma once

#include "UE/T/TTypeCompatibleBytes.h"

namespace UE
{
	template <class T>
	class TPlacementNewer
	{
		using TPlacementNewer_T = T;

	public:
		TPlacementNewer() = default;

		~TPlacementNewer()
		{
			if (constructed)
				((TPlacementNewer_T*)&bytes)->TPlacementNewer_T::~TPlacementNewer_T();
		}

		template <class... U>
		T* operator()(U&&... a_args)
		{
			assert(!constructed);
			T* result = new (&bytes) T(std::forward<U>(a_args)...);
			constructed = true;
			return result;
		}

		T* operator->()
		{
			assert(constructed);
			return (T*)&bytes;
		}

	private:
		TTypeCompatibleBytes<T> bytes;
		bool                    constructed{ false };
	};
}
