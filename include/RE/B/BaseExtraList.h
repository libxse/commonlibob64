#pragma once

#include "RE/E/EXTRA_DATA_TYPE.h"

namespace RE
{
	class BSExtraData;

	class BaseExtraList
	{
	public:
		inline static constexpr auto RTTI = RTTI::BaseExtraList;
		inline static constexpr auto VTABLE = VTABLE::BaseExtraList;

		// add
		virtual ~BaseExtraList();  // 000

		void         AddExtra(BSExtraData* a_extra);
		BSExtraData* GetExtraData(EXTRA_DATA_TYPE a_type) const;
		std::int32_t ItemsInList() const;
		void         RemoveAll(bool a_delete);
		void         RemoveExtra(EXTRA_DATA_TYPE a_type);

		template <class T>
		T* GetExtraData()
		{
			return static_cast<T*>(GetExtraData(T::TYPE));
		}

		// members
		BSExtraData* head;       // 008
		std::uint8_t flags[16];  // 010
	};
	static_assert(sizeof(BaseExtraList) == 0x20);
}

namespace RE
{
	inline void BaseExtraList::AddExtra(BSExtraData* a_extra)
	{
		using func_t = decltype(&BaseExtraList::AddExtra);
		static REL::Relocation<func_t> func{ ID::BaseExtraList::AddExtra };
		func(this, a_extra);
	}

	inline BSExtraData* BaseExtraList::GetExtraData(EXTRA_DATA_TYPE a_type) const
	{
		using func_t = BSExtraData* (BaseExtraList::*)(EXTRA_DATA_TYPE) const;
		static REL::Relocation<func_t> func{ ID::BaseExtraList::GetExtraData };
		return func(this, a_type);
	}

	inline std::int32_t BaseExtraList::ItemsInList() const
	{
		using func_t = decltype(&BaseExtraList::ItemsInList);
		static REL::Relocation<func_t> func{ ID::BaseExtraList::ItemsInList };
		return func(this);
	}

	inline void BaseExtraList::RemoveAll(bool a_delete)
	{
		using func_t = decltype(&BaseExtraList::RemoveAll);
		static REL::Relocation<func_t> func{ ID::BaseExtraList::RemoveAll };
		func(this, a_delete);
	}

	inline void BaseExtraList::RemoveExtra(EXTRA_DATA_TYPE a_type)
	{
		using func_t = decltype(&BaseExtraList::RemoveExtra);
		static REL::Relocation<func_t> func{ ID::BaseExtraList::RemoveExtra };
		func(this, a_type);
	}
}
