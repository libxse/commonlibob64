#pragma once

namespace UE
{
	template <bool CONST, class C, class T>
	class TMemFunPtrType;

	template <class C, class R, class... A>
	class TMemFunPtrType<false, C, R(A...)>
	{
		using Type = R (C::*)(A...);
	};

	template <class C, class R, class... A>
	class TMemFunPtrType<true, C, R(A...)>
	{
		using Type = R (C::*)(A...) const;
	};
}
