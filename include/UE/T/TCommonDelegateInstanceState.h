#pragma once

#include "UE/F/FDelegateHandle.h"
#include "UE/I/IBaseDelegateInstance.h"
#include "UE/T/TTuple.h"

namespace UE
{
	template <class F, class P, class... A>
	class TCommonDelegateInstanceState :
		IBaseDelegateInstance<F, P>
	{
	public:
		template <class... A2>
		explicit TCommonDelegateInstanceState(A2&&... a_args) :
			m_payload(std::forward<A2>(a_args)...),
			m_handle(FDelegateHandle::GenerateNewHandle)
		{}

		FDelegateHandle GetHandle() const
		{
			return m_handle;
		}

	protected:
		TTuple<A...>    m_payload;  // ???
		FDelegateHandle m_handle;   // ???
	};
}
