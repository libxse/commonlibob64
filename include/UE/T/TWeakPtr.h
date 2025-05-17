#pragma once

#include "UE/S/SharedPointerInternals.h"

namespace UE
{
	template <class T, ESPMode>
	class TSharedPtr;

	template <class T, ESPMode>
	class TSharedRef;

	template <class T, ESPMode M>
	class TWeakPtr
	{
		template <class U, ESPMode>
		friend class TWeakPtr;

		template <class U, ESPMode>
		friend class TSharedPtr;

	public:
		TWeakPtr(SharedPointerInternals::FNullTag* = nullptr) :
			object(nullptr), weakReferenceCount()
		{}

		TWeakPtr(TWeakPtr&& a_other) :
			object(a_other.object), weakReferenceCount(std::move(a_other.weakReferenceCount))
		{
			a_other.object = nullptr;
		}

		TWeakPtr(const TWeakPtr& a_other) :
			object(a_other.object), weakReferenceCount(a_other.weakReferenceCount)
		{}

		template <class U>
		TWeakPtr(const TSharedPtr<U, M>& a_sharedPtr)
			requires(std::convertible_to<U*, T*>)
			:
			object(a_sharedPtr.object), weakReferenceCount(a_sharedPtr.sharedReferenceCount)
		{}

		template <class U>
		TWeakPtr(const TSharedRef<U, M>& a_sharedRef)
			requires(std::convertible_to<U*, T*>)
			:
			object(a_sharedRef.object), weakReferenceCount(a_sharedRef.sharedReferenceCount)
		{}

	private:
		// members
		T*                                         object;              // 00
		SharedPointerInternals::FWeakReferencer<M> weakReferenceCount;  // 08
	};
}
