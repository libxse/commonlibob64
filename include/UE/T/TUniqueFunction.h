#pragma once

#include "UE/T/TFunction.h"

namespace UE
{
	template <class T>
	class TUniqueFunction :
		public Core::Private::Function::TFunctionRefBase<Core::Private::Function::TFunctionStorage<true>, T>
	{
		using Super = Core::Private::Function::TFunctionRefBase<Core::Private::Function::TFunctionStorage<true>, T>;

	public:
		TUniqueFunction(std::nullptr_t = nullptr)
		{}

		TUniqueFunction(TFunction<T>&& a_other) :
			Super(MoveTemp(*(Core::Private::Function::TFunctionRefBase<Core::Private::Function::TFunctionStorage<false>, T>*)&a_other))
		{}

		TUniqueFunction(const TFunction<T>& a_other) :
			Super(*(const Core::Private::Function::TFunctionRefBase<Core::Private::Function::TFunctionStorage<false>, T>*)&a_other)
		{}

		template <class F>
		requires(!(TIsTUniqueFunction<std::decay_t<F>>::Value || TIsTFunction<std::decay_t<F>>::Value) && Core::Private::Function::TFuncCanBindToFunctor<T, F>::Value)
		TUniqueFunction(F&& a_function) :
			Super(std::forward<F>(a_function))
		{}

		TUniqueFunction(TUniqueFunction&&) = default;
		TUniqueFunction(const TUniqueFunction&) = delete;
		~TUniqueFunction() = default;

		TUniqueFunction& operator=(const TUniqueFunction&) = delete;

		TUniqueFunction& operator=(TUniqueFunction&& a_other)
		{
			std::swap(*this, a_other);
			return *this;
		}

		explicit operator bool() const
		{
			return Super::IsSet();
		}
	};
}
