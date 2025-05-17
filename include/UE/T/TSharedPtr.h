#pragma once

#include "UE/S/SharedPointerInternals.h"

namespace UE
{
	class UObject;

	template <class T, ESPMode M = ESPMode::ThreadSafe>
	class TSharedPtr
	{
	public:
		TSharedPtr(SharedPointerInternals::FNullTag* = nullptr) :
			object(nullptr), sharedReferenceCount()
		{}

		TSharedPtr(const TSharedPtr& a_other) :
			object(a_other.object), sharedReferenceCount(a_other.sharedReferenceCount)
		{}

		TSharedPtr(TSharedPtr&& a_other) :
			object(a_other.object), sharedReferenceCount(std::move(a_other.sharedReferenceCount))
		{
			a_other.object = nullptr;
		}

		T* Get() const
		{
			return object;
		}

		explicit operator bool() const
		{
			return object;
		}

		T* operator->() const
		{
			assert(object);
			return object;
		}

		// members
		T*                                           object;                // 00
		SharedPointerInternals::FSharedReferencer<M> sharedReferenceCount;  // 08
	};
	static_assert(sizeof(TSharedPtr<void>) == 0x10);
}
