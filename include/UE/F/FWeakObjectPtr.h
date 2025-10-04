#pragma once

#include "UE/F/FObjectPtr.h"
#include "UE/F/FUObjectArray.h"
#include "UE/U/UObject.h"

namespace UE
{
	class FWeakObjectPtr
	{
		friend class FFieldPath;

	public:
		FWeakObjectPtr() = default;

		FWeakObjectPtr(std::nullptr_t) :
			FWeakObjectPtr()
		{}

		FWeakObjectPtr(const UObject* a_object)
		{
			*this = a_object;
		}

		void operator=(const UObject* a_object)
		{
			*this = FObjectPtr(a_object);
		}

		void operator=(FObjectPtr a_object)
		{
			if (auto object = a_object.Get()) {
				const auto objects = FUObjectArray::GetSingleton();
				m_objectIndex = objects->ObjectToIndex(object);
				m_objectSerialNumber = objects->AllocateSerialNumber(m_objectIndex);
			} else {
				Reset();
			}
		}

		void Reset()
		{
			m_objectIndex = 0;
			m_objectSerialNumber = 0;
		}

	private:
		std::int32_t m_objectIndex{ 0 };
		std::int32_t m_objectSerialNumber{ 0 };
	};
	static_assert(sizeof(FWeakObjectPtr) == 0x08);
}
