#pragma once

#include "UE/S/SharedPointerInternals.h"

namespace UE
{
	class UObject;

	template <class T, ESPMode M>
	class TSharedRef
	{
		template <class, ESPMode>
		friend class TSharedPtr;

	public:
		template <class U>
		explicit TSharedRef(U* a_object)
			requires(std::convertible_to<U*, T*>)
			:
			m_object(a_object),
			m_sharedReferenceCount(SharedPointerInternals::NewDefaultReferenceController<M>(a_object))
		{
			Init(a_object);
		}

		TSharedRef(const TSharedRef& a_other) :
			m_object(a_other.m_object), m_sharedReferenceCount(a_other.m_sharedReferenceCount)
		{}

		TSharedRef(TSharedRef&& a_other) :
			m_object(a_other.m_object), m_sharedReferenceCount(a_other.m_sharedReferenceCount)
		{}

		T& Get() const
		{
			return *m_object;
		}

		T& operator*() const
		{
			assert(m_object);
			return *m_object;
		}

		T* operator->() const
		{
			assert(m_object);
			return m_object;
		}

	private:
		template <class T2>
		void Init(T2* a_object)
		{
			assert(a_object);

			SharedPointerInternals::EnableSharedFromThis(this, a_object, a_object);
		}

	private:
		// members
		T*                                           m_object;                // 000
		SharedPointerInternals::FSharedReferencer<M> m_sharedReferenceCount;  // 008
	};
	static_assert(sizeof(TSharedRef<class _TEST>) == 0x10);
}
