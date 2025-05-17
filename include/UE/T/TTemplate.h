#pragma once

#include "UE/F/FMemory.h"
#include "UE/T/TCopyQualifiersAndRefsFromTo.h"
#include "UE/T/TTypeTraits.h"

namespace UE
{
	template <typename T>
	T CopyTemp(T& a_value)
	{
		return const_cast<const T&>(a_value);
	}

	template <typename T>
	T CopyTemp(const T& a_value)
	{
		return a_value;
	}

	template <class T1, class T2>
	requires(std::is_convertible_v<std::remove_reference_t<T1>*, const volatile T2*>)
	decltype(auto) ForwardAsBase(std::remove_reference_t<T1>& a_object)
	{
		return (TCopyQualifiersAndRefsFromTo_T<T1&&, T2>)a_object;
	}

	template<class T1, class T2>
	requires(std::is_convertible_v<std::remove_reference_t<T1>*, const volatile T2*>)
	decltype(auto) ForwardAsBase(std::remove_reference_t<T1>&& a_object)
	{
		return (TCopyQualifiersAndRefsFromTo_T<T1&&, T2>)a_object;
	}

	template <class T>
	std::remove_reference_t<T>&& MoveTemp(T&& a_object)
	{
		static_assert(std::is_lvalue_reference_v<T>, "MoveTemp called on an rvalue");
		static_assert(!std::is_same_v<std::remove_reference_t<T>&, const std::remove_reference_t<T>&>, "MoveTemp called on a const object");

		return (std::remove_reference_t<T>&&)a_object;
	}

	template <class T1, class T2, class S>
	void ConstructItems(void* a_dst, const T2* a_src, S a_count)
	{
		if constexpr (TIsBitwiseConstructible<T1, T2>::Value) {
			if (a_count)
				FMemory::Memcpy(a_dst, a_src, sizeof(T2) * a_count);
		} else {
			while (a_count) {
				new (a_dst) T1(*a_src);
				++(T1*&)a_dst;
				++a_src;
				--a_count;
			}
		}
	}
}
