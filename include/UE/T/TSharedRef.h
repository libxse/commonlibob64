#pragma once

#include "UE/S/SharedPointerInternals.h"

namespace UE
{
	class UObject;

	template <class T, ESPMode M = ESPMode::ThreadSafe>
	class TSharedRef
	{
	public:
		template <class U>
		explicit TSharedRef(U* a_object)
			requires(std::convertible_to<U*, T*>) :
			object(a_object), sharedReferenceCount(SharedPointerInternals::NewDefaultReferenceController<M>(a_object))
		{
			Init(a_object);
		}

		TSharedRef(const TSharedRef& a_other) :
			object(a_other.object), sharedReferenceCount(a_other.sharedReferenceCount)
		{}

		TSharedRef(TSharedRef&& a_other) :
			object(a_other.object), sharedReferenceCount(a_other.sharedReferenceCount)
		{}

		T& Get() const
		{
			return *object;
		}

		template <class U>
		void Init(U* a_object)
		{
			assert(a_object);

			SharedPointerInternals::EnableSharedFromThis(this, a_object, a_object);
		}

		T& operator*() const
		{
			assert(object);
			return *object;
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
	static_assert(sizeof(TSharedRef<class _TEST>) == 0x10);
}
