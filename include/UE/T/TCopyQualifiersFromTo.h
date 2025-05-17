#pragma once

namespace UE
{
	template <class T1, class T2>
	struct TCopyQualifiersFromTo
	{
		using Type = T2;
	};

	template <class T1, class T2>
	struct TCopyQualifiersFromTo<const T1, T2>
	{
		using Type = const T2;
	};

	template <class T1, class T2>
	struct TCopyQualifiersFromTo<volatile T1, T2>
	{
		using Type = volatile T2;
	};

	template <class T1, class T2>
	struct TCopyQualifiersFromTo<const volatile T1, T2>
	{
		using Type = const volatile T2;
	};
}
