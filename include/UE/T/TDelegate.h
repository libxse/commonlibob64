#pragma once

#include "UE/F/FDefaultDelegateUserPolicy.h"
#include "UE/T/TMemFunPtrType.h"

namespace UE
{
	template <class T, class P = FDefaultDelegateUserPolicy>
	class TDelegate
	{
		static_assert(sizeof(P) == 0);
	};

	template <class R, class... A, class P>
	class TDelegate<R(A...), P> :
		public P::FDelegateExtras
	{
	public:
		using FuncType = R(A...);

		template <class U2, class... T2>
		using TMethodPtr = typename TMemFunPtrType<false, U2, R(A..., T2...)>::Type;
	};
}
