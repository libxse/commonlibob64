#pragma once

#include "UE/T/TTuple.h"

namespace UE
{
	template <class T1, class T2>
	using TPair = TTuple<T1, T2>;

	template <class T1, class T2>
	class TPairInitializer
	{
	public:
		TPairInitializer(T1 a_first, T2 a_second) :
			key(a_first), value(a_second)
		{}

		template <class U1, class U2>
		TPairInitializer(const TPair<U1, U2>& a_pair) :
			key(a_pair.key), value(a_pair.value)
		{}

		template <class U1, class U2>
		operator TPair<U1, U2>() const
		{
			return TPair<U1, U2>(static_cast<T1>(key), static_cast<T2>(value));
		}

		// members
		TRValueToLValueReference<T1>::Type key;
		TRValueToLValueReference<T2>::Type value;
	};
}
