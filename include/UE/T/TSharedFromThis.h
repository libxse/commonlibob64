#pragma once

#include "UE/T/TSharedPtr.h"
#include "UE/T/TSharedRef.h"
#include "UE/T/TWeakPtr.h"

namespace UE
{
	template <class T, ESPMode M>
	class TSharedFromThis
	{
	public:
		template <class U1, class U2>
		void UpdateWeakReferenceInternal(const TSharedPtr<U1, M>* a_sharedPtr, U2* a_object) const
		{
			if (!weakThis.IsValid())
				weakThis = TSharedPtr<T, M>(*a_sharedPtr, a_object);
		}

		template <class U1, class U2>
		void UpdateWeakReferenceInternal(const TSharedRef<U1, M>* a_sharedRef, U2* a_object) const
		{
			if (!weakThis.IsValid())
				weakThis = TSharedRef<T, M>(*a_sharedRef, a_object);
		}

	protected:
		TSharedFromThis() {}
		TSharedFromThis(const TSharedFromThis&) {}
		~TSharedFromThis() {}

		TSharedFromThis& operator=(const TSharedFromThis&)
		{
			return *this;
		}

	public:
		// members
		mutable TWeakPtr<T, M> weakThis;
	};
}
