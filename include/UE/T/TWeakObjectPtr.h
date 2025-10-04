#pragma once

#include "UE/F/FWeakObjectPtr.h"

namespace UE
{
	class UObject;

	template <class T = UObject, class B = FWeakObjectPtr>
	class TWeakObjectPtr
	{
		friend class FFieldPath;

	public:
		TWeakObjectPtr() = default;

		TWeakObjectPtr(std::nullptr_t) :
			m_weakPtr((const UObject*)nullptr)
		{}

		template <class U, std::enable_if_t<std::is_convertible_v<U, T*>, int> = 0>
		TWeakObjectPtr(U a_object) :
			m_weakPtr((const UObject*)a_object)
		{
			//static_assert(std::is_convertible_v<T*, const volatile UObject*>);
		}

	private:
		B m_weakPtr;  // 000
	};
	static_assert(sizeof(TWeakObjectPtr<UObject>) == 0x08);
}
