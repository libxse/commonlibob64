#pragma once

namespace UE
{
	template <class T1, class T2>
	struct TIsBitwiseConstructible
	{
		static_assert(!std::is_reference_v<T1> && !std::is_reference_v<T2>);
		static_assert(std::is_same_v<T1, std::remove_cv_t<T1>> && std::is_same_v<T2, std::remove_cv_t<T2>>);

		static constexpr bool Value{ false };
	};

	template <class T>
	struct TIsBitwiseConstructible<T, T>
	{
		static constexpr bool Value{ std::is_trivially_copy_constructible_v<T> };
	};

	template <typename T, typename U>
	struct TIsBitwiseConstructible<const T, U> :
		TIsBitwiseConstructible<T, U>
	{};

	template <typename T>
	struct TIsBitwiseConstructible<const T*, T*>
	{
		static constexpr bool Value{ true };
	};

	template <>
	struct TIsBitwiseConstructible<std::uint8_t, std::int8_t>
	{
		static constexpr bool Value{ true };
	};

	template <>
	struct TIsBitwiseConstructible<std::int8_t, std::uint8_t>
	{
		static constexpr bool Value{ true };
	};

	template <>
	struct TIsBitwiseConstructible<std::uint16_t, std::int16_t>
	{
		static constexpr bool Value{ true };
	};

	template <>
	struct TIsBitwiseConstructible<std::int16_t, std::uint16_t>
	{
		static constexpr bool Value{ true };
	};

	template <>
	struct TIsBitwiseConstructible<std::uint32_t, std::int32_t>
	{
		static constexpr bool Value{ true };
	};

	template <>
	struct TIsBitwiseConstructible<std::int32_t, std::uint32_t>
	{
		static constexpr bool Value{ true };
	};

	template <>
	struct TIsBitwiseConstructible<std::uint64_t, std::int64_t>
	{
		static constexpr bool Value{ true };
	};

	template <>
	struct TIsBitwiseConstructible<std::int64_t, std::uint64_t>
	{
		static constexpr bool Value{ true };
	};
}

namespace UE
{
	template <class T>
	class TFunction;

	template <class T>
	class TFunctionRef;

	template <class T>
	class TUniqueFunction;

	template <class T>
	struct TIsTFunction
	{
		static constexpr bool Value{ false };
	};

	template <class T>
	struct TIsTFunction<TFunction<T>>
	{
		static constexpr bool Value{ true };
	};

	template <class T>
	struct TIsTFunction<const T>
	{
		static constexpr bool Value{ TIsTFunction<T>::Value };
	};

	template <class T>
	struct TIsTFunction<volatile T>
	{
		static constexpr bool Value{ TIsTFunction<T>::Value };
	};

	template <class T>
	struct TIsTFunction<const volatile T>
	{
		static constexpr bool Value{ TIsTFunction<T>::Value };
	};

	template <class T>
	struct TIsTUniqueFunction
	{
		static constexpr bool Value{ false };
	};

	template <class T>
	struct TIsTUniqueFunction<TUniqueFunction<T>>
	{
		static constexpr bool Value{ true };
	};

	template <class T>
	struct TIsTUniqueFunction<const T>
	{
		static constexpr bool Value{ TIsTUniqueFunction<T>::Value };
	};

	template <class T>
	struct TIsTUniqueFunction<volatile T>
	{
		static constexpr bool Value{ TIsTUniqueFunction<T>::Value };
	};

	template <class T>
	struct TIsTUniqueFunction<const volatile T>
	{
		static constexpr bool Value{ TIsTUniqueFunction<T>::Value };
	};

	template <class T>
	struct TIsTFunctionRef
	{
		static constexpr bool Value{ false };
	};

	template <class T>
	struct TIsTFunctionRef<TFunctionRef<T>>
	{
		static constexpr bool Value{ true };
	};

	template <class T>
	struct TIsTFunctionRef<const T>
	{
		static constexpr bool Value{ TIsTFunctionRef<T>::Value };
	};

	template <class T>
	struct TIsTFunctionRef<volatile T>
	{
		static constexpr bool Value{ TIsTFunctionRef<T>::Value };
	};

	template <class T>
	struct TIsTFunctionRef<const volatile T>
	{
		static constexpr bool Value{ TIsTFunctionRef<T>::Value };
	};
}

namespace UE
{
	template <class T>
	struct TRValueToLValueReference
	{
		using Type = T;
	};

	template <class T>
	struct TRValueToLValueReference<T&&>
	{
		using Type = T&;
	};
}
