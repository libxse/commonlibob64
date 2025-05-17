#pragma once

namespace UE
{
	template <class... T>
	inline void LowLevelFatalErrorHandler(const char* a_file, std::int32_t a_line, void* a_programCounter, const wchar_t* a_format = L"", T... a_args)
	{
		using func_t = decltype(&LowLevelFatalErrorHandler<T...>);
		REL::Relocation<func_t> func{ ID::LowLevelFatalErrorHandler };
		func(a_file, a_line, a_programCounter, a_format, a_args...);
	}

	template <class... T>
	struct LowLevelFatalError
	{
		LowLevelFatalError() = delete;

		explicit LowLevelFatalError(const std::wformat_string<T...> a_format, T&&... a_args, const std::source_location a_loc = std::source_location::current())
		{
			const auto str = std::vformat(a_format.get(), std::make_wformat_args(a_args...));
			LowLevelFatalErrorHandler(a_loc.file_name(), static_cast<std::int32_t>(a_loc.line()), _ReturnAddress(), str.c_str());
		}
	};
}
