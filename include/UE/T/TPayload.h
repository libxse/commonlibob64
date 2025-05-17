#pragma once

#include "UE/T/TTuple.h"

namespace UE
{
	template <class T>
	class TPayload;

	template <class R, class... T>
	class TPayload<R(T...)>
	{
	public:
		template <class... U>
		explicit TPayload(U&&... a_args) :
			values(std::forward<U>(a_args)..., R())
		{}

		R& GetResult()
		{
			return values.template Get<sizeof...(T)>();
		}

		// members
		TTuple<T..., R> values;  // 00
	};

	template <class... T>
	class TPayload<void(T...)>
	{
	public:
		template <class... U>
		explicit TPayload(U&&... a_args) :
			values(std::forward<U>(a_args)...)
		{}

		void GetResult() {}

		// members
		TTuple<T...> values;  // 00
	};
}
