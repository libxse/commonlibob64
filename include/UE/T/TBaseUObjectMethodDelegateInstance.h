#pragma once

#include "UE/T/TCommonDelegateInstanceState.h"
#include "UE/T/TMemFunPtrType.h"
#include "UE/T/TWeakObjectPtr.h"

namespace UE
{
	template <bool CONST, class U, class F, class P, class... V>
	class TBaseUObjectMethodDelegateInstance;

	template <bool CONST, class U, class R, class... A, class P, class... V>
	class TBaseUObjectMethodDelegateInstance<CONST, U, R(A...), P, V...> :
		public TCommonDelegateInstanceState<R(A...), P, V...>
	{
	public:
		using Super = TCommonDelegateInstanceState<R(A...), P, V...>;
		using FMethodPtr = typename TMemFunPtrType<CONST, U, R(A..., V...)>::Type;

		template <class... V2>
		explicit TBaseUObjectMethodDelegateInstance(U* a_object, FMethodPtr a_method, V2&&... a_vars) :
			Super(std::forward<V2>(a_vars)...), m_object(a_object), a_method(a_method)
		{}

	protected:
		TWeakObjectPtr<U> m_object;  // ???
		FMethodPtr        a_method;  // ???
	};
}
