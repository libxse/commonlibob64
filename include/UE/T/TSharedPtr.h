#pragma once

#include "UE/S/SharedPointerInternals.h"
#include "UE/T/TSharedRef.h"

namespace UE
{
	class UObject;

	template <class T, ESPMode M>
	class TSharedPtr
	{
	public:
		TSharedPtr(SharedPointerInternals::FNullTag* = nullptr)
		{}

		TSharedPtr(const TSharedPtr& a_other) :
			m_object(a_other.m_object), m_sharedReferenceCount(a_other.m_sharedReferenceCount)
		{}

		TSharedPtr(TSharedPtr&& a_other) :
			m_object(a_other.m_object), m_sharedReferenceCount(std::move(a_other.m_sharedReferenceCount))
		{
			a_other.m_object = nullptr;
		}

		template <class T2>
		TSharedPtr(const TSharedRef<T2, M>& a_ref) :
			m_object(a_ref.m_object), m_sharedReferenceCount(a_ref.m_sharedReferenceCount)
		{}

		T* Get() const
		{
			return m_object;
		}

		explicit operator bool() const
		{
			return m_object;
		}

		T* operator->() const
		{
			assert(m_object);
			return m_object;
		}

	private:
		// members
		T*                                           m_object{ nullptr };     // 00
		SharedPointerInternals::FSharedReferencer<M> m_sharedReferenceCount;  // 08
	};
	static_assert(sizeof(TSharedPtr<void>) == 0x10);
}
