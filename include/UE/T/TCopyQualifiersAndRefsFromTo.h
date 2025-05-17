#pragma once

#include "UE/T/TCopyQualifiersFromTo.h"

namespace UE
{
	template <class T1, class T2>
	struct TCopyQualifiersAndRefsFromTo
	{
		using Type = TCopyQualifiersFromTo<T1, T2>::Type;
	};

	template <class T1, class T2>
	struct TCopyQualifiersAndRefsFromTo<T1, T2&>
	{
		using Type = TCopyQualifiersFromTo<T1, T2>::Type&;
	};

	template <class T1, class T2>
	struct TCopyQualifiersAndRefsFromTo<T1, T2&&>
	{
		using Type = TCopyQualifiersFromTo<T1, T2>::Type&&;
	};

	template <class T1, class T2>
	struct TCopyQualifiersAndRefsFromTo<T1&, T2>
	{
		using Type = TCopyQualifiersFromTo<T1, T2>::Type&;
	};

	template <class T1, class T2>
	struct TCopyQualifiersAndRefsFromTo<T1&, T2&>
	{
		using Type = TCopyQualifiersFromTo<T1, T2>::Type&;
	};

	template <class T1, class T2>
	struct TCopyQualifiersAndRefsFromTo<T1&, T2&&>
	{
		using Type = TCopyQualifiersFromTo<T1, T2>::Type&;
	};

	template <class T1, class T2>
	struct TCopyQualifiersAndRefsFromTo<T1&&, T2>
	{
		using Type = TCopyQualifiersFromTo<T1, T2>::Type&&;
	};

	template <class T1, class T2>
	struct TCopyQualifiersAndRefsFromTo<T1&&, T2&>
	{
		using Type = TCopyQualifiersFromTo<T1, T2>::Type&;
	};

	template <class T1, class T2>
	struct TCopyQualifiersAndRefsFromTo<T1&&, T2&&>
	{
		using Type = TCopyQualifiersFromTo<T1, T2>::Type&&;
	};

	template <class T1, class T2>
	using TCopyQualifiersAndRefsFromTo_T = TCopyQualifiersAndRefsFromTo<T1, T2>::Type;
}
