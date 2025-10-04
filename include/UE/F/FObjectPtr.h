#pragma once

#include "UE/F/FObjectHandle.h"

namespace UE
{
	class FObjectPtr
	{
	public:
		FObjectPtr() :
			m_handle(nullptr)
		{}

		FObjectPtr(std::nullptr_t) :
			m_handle(nullptr)
		{}

		FObjectPtr(const UObject* a_object) :
			m_handle(const_cast<UObject*>(a_object))
		{}

		UObject* Get() const
		{
			return m_handle;
		}

		explicit operator bool() const
		{
			return m_handle;
		}

	private:
		union
		{
			mutable FObjectHandle m_handle;
			UObject*              m_debugPtr;
		};
	};
	static_assert(sizeof(FObjectPtr) == 0x08);
}
