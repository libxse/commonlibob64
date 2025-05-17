#pragma once

#include "UE/T/TIntegerSequence.h"

namespace UE::Core::Private::Tuple
{
	enum EForwardingConstructor
	{
		ForwardingConstructor
	};

	enum EOtherTupleConstructor
	{
		OtherTupleConstructor
	};

	template <class... T>
	void ConceptCheckingHelper(T&&...);

	template <class... T1, class... T2>
	decltype(ConceptCheckingHelper((std::declval<T1>() = std::declval<T2&&>(), 0)...)) AssignableConceptCheck(T2&&...);

	template <class... T1, class... T2>
	std::enable_if_t<std::conjunction_v<std::is_constructible<T1, T2&&>...>> ConstructibleConceptCheck(T2&&...);

	template <class T, std::uint32_t I, std::uint32_t S>
	class TTupleBaseElement
	{
	public:
		TTupleBaseElement() = default;

		template <class U>
		requires(std::is_constructible_v<T, U&&>)
		explicit TTupleBaseElement(EForwardingConstructor, U&& a_arg) :
			value(std::forward<U>(a_arg))
		{}

		// members
		T value{};  // 00
	};

	template <class T>
	class TTupleBaseElement<T, 0, 2>
	{
	public:
		TTupleBaseElement() = default;

		template <class U>
		requires(std::is_constructible_v<T, U&&>)
		explicit TTupleBaseElement(EForwardingConstructor, U&& a_arg) :
			key(std::forward<U>(a_arg))
		{}

		// members
		T key{};  // 00
	};

	template <std::uint32_t I, std::uint32_t S>
	class TTupleElementGetterByIndex
	{
	public:
		template <class T1, class T2>
		static decltype(auto) GetImpl(const volatile TTupleBaseElement<T1, I, S>&, T2&& a_tuple)
		{
			decltype(auto) value = (ForwardAsBase<T2, TTupleBaseElement<T1, I, S>>(a_tuple).value);
			return static_cast<std::conditional_t<!std::is_reference_v<T2> && std::is_rvalue_reference_v<T1>, T1, decltype(value)>>(value);
		}

		template <class T>
		static decltype(auto) Get(T&& a_tuple)
		{
			return GetImpl(a_tuple, std::forward<T>(a_tuple));
		}
	};

	template <>
	class TTupleElementGetterByIndex<0, 2>
	{
	public:
		template <class T>
		static decltype(auto) Get(T&& a_tuple)
		{
			decltype(auto) key = (ForwardAsBase<T, TTupleBaseElement<decltype(a_tuple.key), 0, 2>>(a_tuple).key);
			return static_cast<std::conditional_t<!std::is_reference_v<T> && std::is_rvalue_reference_v<decltype(a_tuple.key)>, decltype(a_tuple.key), decltype(key)>>(key);
		}
	};

	template <class T, std::uint32_t S>
	class TTupleElementGetterByType
	{
	public:
		template <std::uint32_t I, class U>
		static decltype(auto) GetImpl(const volatile TTupleBaseElement<T, I, S>&, U&& a_tuple)
		{
			return TTupleElementGetterByIndex<I, S>::Get(std::forward<U>(a_tuple));
		}

		template <class U>
		static decltype(auto) Get(U&& a_tuple)
		{
			return GetImpl(a_tuple, std::forward<U>(a_tuple));
		}
	};

	template <class I, class... T>
	class TTupleBase;

	template <std::uint32_t... I, class... T>
	class TTupleBase<TIntegerSequence<std::uint32_t, I...>, T...> :
		public TTupleBaseElement<T, I, sizeof...(T)>...
	{
	public:
		TTupleBase() = default;

		template <class... U, decltype(ConceptCheckingHelper(TTupleBaseElement<T, I, sizeof...(T)>(ForwardingConstructor, std::declval<U&&>())...))* = nullptr>
		explicit TTupleBase(EForwardingConstructor, U&&... a_args) :
			TTupleBaseElement<T, I, sizeof...(T)>(ForwardingConstructor, std::forward<U>(a_args))...
		{}

		template <class U, decltype(ConceptCheckingHelper(TTupleBaseElement<T, I, sizeof...(T)>(ForwardingConstructor, std::declval<U&&>().template Get<I>())...))* = nullptr>
		explicit TTupleBase(EOtherTupleConstructor, U&& a_other) :
			TTupleBaseElement<T, I, sizeof...(T)>(ForwardingConstructor, std::forward<U>(a_other).template Get<I>())...
		{}

		template <std::uint32_t IX>
		decltype(auto) Get() &
		{
			static_assert(IX < sizeof...(T), "Invalid index");
			return TTupleElementGetterByIndex<IX, sizeof...(T)>::Get(static_cast<TTupleBase&>(*this));
		}

		template <std::uint32_t IX>
		decltype(auto) Get() const&
		{
			static_assert(IX < sizeof...(T), "Invalid index");
			return TTupleElementGetterByIndex<IX, sizeof...(T)>::Get(static_cast<const TTupleBase&>(*this));
		}

		template <std::uint32_t IX>
		decltype(auto) Get() volatile&
		{
			static_assert(IX < sizeof...(T), "Invalid index");
			return TTupleElementGetterByIndex<IX, sizeof...(T)>::Get(static_cast<volatile TTupleBase&>(*this));
		}

		template <std::uint32_t IX>
		decltype(auto) Get() const volatile&
		{
			static_assert(IX < sizeof...(T), "Invalid index");
			return TTupleElementGetterByIndex<IX, sizeof...(T)>::Get(static_cast<const volatile TTupleBase&>(*this));
		}

		template <std::uint32_t IX>
		decltype(auto) Get() &&
		{
			static_assert(IX < sizeof...(T), "Invalid index");
			return TTupleElementGetterByIndex<IX, sizeof...(T)>::Get(static_cast<TTupleBase&&>(*this));
		}

		template <std::uint32_t IX>
		decltype(auto) Get() const&&
		{
			static_assert(IX < sizeof...(T), "Invalid index");
			return TTupleElementGetterByIndex<IX, sizeof...(T)>::Get(static_cast<const TTupleBase&&>(*this));
		}

		template <std::uint32_t IX>
		decltype(auto) Get() volatile&&
		{
			static_assert(IX < sizeof...(T), "Invalid index");
			return TTupleElementGetterByIndex<IX, sizeof...(T)>::Get(static_cast<volatile TTupleBase&&>(*this));
		}

		template <std::uint32_t IX>
		decltype(auto) Get() const volatile&&
		{
			static_assert(IX < sizeof...(T), "Invalid index");
			return TTupleElementGetterByIndex<IX, sizeof...(T)>::Get(static_cast<const volatile TTupleBase&&>(*this));
		}
	};
}

namespace UE
{
	template <class... T>
	class TTuple :
		public Core::Private::Tuple::TTupleBase<TMakeIntegerSequence<std::uint32_t, sizeof...(T)>, T...>
	{
		using Super = Core::Private::Tuple::TTupleBase<TMakeIntegerSequence<std::uint32_t, sizeof...(T)>, T...>;

	public:
		TTuple() = default;

		template <class... U, decltype(Core::Private::Tuple::ConstructibleConceptCheck<T...>(std::declval<U&&>()...))* = nullptr>
		explicit(!std::conjunction_v<std::is_convertible<U&&, T>...>) TTuple(U&&... a_args) :
			Super(Core::Private::Tuple::ForwardingConstructor, std::forward<U>(a_args)...)
		{}

		template <class... U, decltype(Core::Private::Tuple::ConstructibleConceptCheck<T...>(std::declval<U&&>()...))* = nullptr>
		TTuple(TTuple<U...>&& a_other) :
			Super(Core::Private::Tuple::OtherTupleConstructor, std::move(a_other))
		{}
	};
	static_assert(sizeof(TTuple<void*, void*>) == 0x10);
}
