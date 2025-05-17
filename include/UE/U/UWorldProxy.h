#pragma once

#include "UE/UnrealGlobal.h"

namespace UE
{
	class UWorld;

	class UWorldProxy
	{
		friend class UWorld;

	public:
		UWorldProxy() = default;

		UWorld* operator->()
		{
			assert(IsInGameThread());
			return m_world;
		}

		const UWorld* operator->() const
		{
			assert(IsInGameThread());
			return m_world;
		}

		operator UWorld*() const
		{
			assert(IsInGameThread());
			return m_world;
		}

		explicit operator bool() const
		{
			return m_world;
		}

	private:
		UWorldProxy(UWorld* a_world) :
			m_world(a_world)
		{}

	private:
		UWorld* m_world{ nullptr };  // 00
	};
	static_assert(sizeof(UWorldProxy) == 0x8);
}
