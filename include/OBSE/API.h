#pragma once

#include "REX/REX/LOG.h"

namespace OBSE
{
	using PluginHandle = std::uint32_t;

	struct PluginInfo;

	class PreLoadInterface;
	class LoadInterface;
	class MessagingInterface;
	class TrampolineInterface;

	struct InitInfo
	{
		bool        log{ true };
#ifndef NDEBUG
		REX::LOG_LEVEL logLevel{ REX::LOG_LEVEL::DEBUG };
#else
		REX::LOG_LEVEL logLevel{ REX::LOG_LEVEL::INFO };
#endif
		const char* logName{ nullptr };
		const char* logPattern{ nullptr };
		bool        trampoline{ false };
		std::size_t trampolineSize{ 0 };
		bool        hook{ true };
	};

	void Init(const PreLoadInterface* a_intfc, InitInfo a_info = {}) noexcept;
	void Init(const LoadInterface* a_intfc, InitInfo a_info = {}) noexcept;

	[[nodiscard]] OBSE::Version     GetOBSEVersion() noexcept;
	[[nodiscard]] std::string_view  GetPluginName() noexcept;
	[[nodiscard]] std::string_view  GetPluginAuthor() noexcept;
	[[nodiscard]] OBSE::Version     GetPluginVersion() noexcept;
	[[nodiscard]] PluginHandle      GetPluginHandle() noexcept;
	[[nodiscard]] const PluginInfo* GetPluginInfo(std::string_view a_plugin) noexcept;
	[[nodiscard]] std::uint32_t     GetReleaseIndex() noexcept;
	[[nodiscard]] std::string_view  GetSaveFolderName() noexcept;

	[[nodiscard]] const MessagingInterface*  GetMessagingInterface() noexcept;
	[[nodiscard]] const TrampolineInterface* GetTrampolineInterface() noexcept;
}
