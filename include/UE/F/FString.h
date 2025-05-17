#pragma once

#include "UE/E/ESearchCase.h"
#include "UE/T/TArray.h"

namespace UE
{
	class FString
	{
	public:
		FString() = default;
		FString(FString&&) = default;
		FString(const FString&) = default;
		FString& operator=(FString&&) = default;
		FString& operator=(const FString&) = default;

		FString(const char* a_str)
		{
			using func_t = void (*)(FString*, const char*);
			static REL::Relocation<func_t> func{ ID::FString::Ctor1 };
			func(this, a_str);
		}

		FString(const wchar_t* a_str)
		{
			using func_t = void (*)(FString*, const wchar_t*);
			static REL::Relocation<func_t> func{ ID::FString::Ctor2 };
			func(this, a_str);
		}

		bool IsEmpty() const
		{
			return data.Num() <= 1;
		}

		std::int32_t Len() const
		{
			return data.Num() ? data.Num() - 1 : 0;
		}

		bool Equals(const FString& a_other, ESearchCase a_searchCase = ESearchCase::CaseSensitive) const
		{
			std::int32_t num = data.Num();
			std::int32_t numOther = a_other.data.Num();

			if (num != numOther) {
				return num + numOther == 1;
			} else if (num > 1) {
				if (a_searchCase == ESearchCase::CaseSensitive) {
					return std::wcscmp(data.GetData(), a_other.data.GetData()) == 0;
				} else {
					return _wcsicmp(data.GetData(), a_other.data.GetData()) == 0;
				}
			}

			return true;
		}

		wchar_t* begin()
		{
			return data.begin();
		}

		const wchar_t* begin() const
		{
			return data.begin();
		}

		wchar_t* end()
		{
			auto result = data.end();
			return data.Num() ? --result : result;
		}

		const wchar_t* end() const
		{
			auto result = data.end();
			return data.Num() ? --result : result;
		}

		bool operator==(const FString& a_rhs) const
		{
			return Equals(a_rhs, ESearchCase::IgnoreCase);
		}

		bool operator!=(const FString& a_rhs) const
		{
			return !Equals(a_rhs, ESearchCase::IgnoreCase);
		}

		bool operator==(const wchar_t* a_rhs) const
		{
			return _wcsicmp(**this, a_rhs) == 0;
		}

		bool operator!=(const wchar_t* a_rhs) const
		{
			return _wcsicmp(**this, a_rhs) != 0;
		}

		friend bool operator==(const wchar_t* a_lhs, const FString& a_rhs)
		{
			return _wcsicmp(a_lhs, *a_rhs) == 0;
		}

		friend bool operator!=(const wchar_t* a_lhs, const FString& a_rhs)
		{
			return _wcsicmp(a_lhs, *a_rhs) != 0;
		}

		const wchar_t* operator*() const
		{
			return data.Num() ? data.GetData() : L"";
		}

		// members
		TArray<wchar_t> data;  // 00
	};
	static_assert(sizeof(FString) == 0x10);
}

template <>
struct std::formatter<UE::FString, wchar_t> : formatter<const wchar_t*, wchar_t>
{
	template <class FormatContext>
	constexpr auto format(const UE::FString& a_str, FormatContext& a_ctx) const
	{
		return formatter<const wchar_t*, wchar_t>::format(*a_str, a_ctx);
	}
};

template <>
struct std::formatter<UE::FString, char> : formatter<std::string, char>
{
	template <class FormatContext>
	constexpr auto format(const UE::FString& a_str, FormatContext& a_ctx) const
	{
		const auto cvt = [&](char* a_dst, const std::size_t a_length) {
			return REX::W32::WideCharToMultiByte(
				REX::W32::CP_UTF8, 0, a_str.begin(), a_str.Len(), a_dst, static_cast<int>(a_length), nullptr, nullptr);
		};

		const auto len = cvt(nullptr, 0);
		if (len == 0) {
			return formatter<std::string, char>::format("", a_ctx);
		}

		std::string str(len, '\0');
		if (cvt(str.data(), str.length()) == 0) {
			return formatter<std::string, char>::format("", a_ctx);
		}

		return formatter<std::string, char>::format(str, a_ctx);
	}
};
