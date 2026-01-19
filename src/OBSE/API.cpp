#include "OBSE/API.h"
#include "OBSE/Interfaces.h"

#include "REL/Hook.h"
#include "REL/Trampoline.h"
#include "REX/REX/Singleton.h"
#include "REX/W32/OLE32.h"
#include "REX/W32/SHELL32.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/spdlog.h>

namespace OBSE
{
	namespace Impl
	{
		struct API :
			public REX::Singleton<API>
		{
			void Init(InitInfo, const OBSE::QueryInterface* a_intfc);
			void InitLog();
			void InitTrampoline();
			void InitHook(REL::HOOK_STEP a_step);

			InitInfo info;

			std::string   pluginName{};
			std::string   pluginAuthor{};
			OBSE::Version pluginVersion{};

			OBSE::Version                                    obse64Version{};
			PluginHandle                                     pluginHandle{ static_cast<PluginHandle>(-1) };
			std::uint32_t                                    releaseIndex{ 0 };
			std::function<const void*(OBSEAPI)(const char*)> pluginInfoAccessor;
			std::string                                      saveFolderName{};

			MessagingInterface*  messagingInterface{ nullptr };
			TrampolineInterface* trampolineInterface{ nullptr };
		};

		void API::Init(InitInfo a_info, const OBSE::QueryInterface* a_intfc)
		{
			info = a_info;

			static std::once_flag once;
			std::call_once(once, [&]() {
				if (const auto data = PluginVersionData::GetSingleton()) {
					pluginName = data->GetPluginName();
					pluginAuthor = data->GetAuthorName();
					pluginVersion = data->GetPluginVersion();
				} else {
					std::vector<char> buf(REX::W32::MAX_PATH, '\0');
					const auto        size = REX::W32::GetModuleFileNameA(REX::W32::GetCurrentModule(), buf.data(), REX::W32::MAX_PATH);
					if (size) {
						std::filesystem::path p(buf.begin(), buf.begin() + size);
						pluginName = p.stem().string();
					}
				}

				obse64Version = a_intfc->OBSEVersion();
				pluginHandle = a_intfc->GetPluginHandle();
				releaseIndex = a_intfc->GetReleaseIndex();
				pluginInfoAccessor = reinterpret_cast<const Impl::OBSEInterface*>(a_intfc)->GetPluginInfo;
				saveFolderName = a_intfc->GetSaveFolderName();
			});
		}

		void API::InitLog()
		{
			if (info.log) {
				static std::once_flag once;
				std::call_once(once, [&]() {
					if (saveFolderName.empty())
						return;

					wchar_t*                                                       knownBuffer{ nullptr };
					const auto                                                     knownResult = REX::W32::SHGetKnownFolderPath(REX::W32::FOLDERID_Documents, REX::W32::KF_FLAG_DEFAULT, nullptr, std::addressof(knownBuffer));
					std::unique_ptr<wchar_t[], decltype(&REX::W32::CoTaskMemFree)> knownPath(knownBuffer, REX::W32::CoTaskMemFree);
					if (!knownPath || knownResult != 0) {
						REX::ERROR("failed to get known folder path");
						return;
					}

					std::filesystem::path path = knownPath.get();
					path /= std::format("My Games/{}/OBSE/Logs/{}.log", GetSaveFolderName(), info.logName ? info.logName : GetPluginName());

					std::vector<spdlog::sink_ptr> sinks{
						std::make_shared<spdlog::sinks::msvc_sink_mt>()
					};

					if (info.logRotate > 0) {
						constexpr auto maxSize = std::numeric_limits<std::size_t>::max();
						sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(path.string(), maxSize, info.logRotate, true));
					} else {
						sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(path.string(), true));
					}

					auto logger = std::make_shared<spdlog::logger>("global", sinks.begin(), sinks.end());
					logger->set_level(static_cast<spdlog::level::level_enum>(info.logLevel));
					logger->flush_on(static_cast<spdlog::level::level_enum>(info.logLevel));

					spdlog::set_default_logger(std::move(logger));
					spdlog::set_pattern(info.logPattern ? info.logPattern : "[%T.%e] [%=5t] [%L] %v");

					REX::INFO("{} v{}", GetPluginName(), GetPluginVersion());
				});
			}
		}

		void API::InitTrampoline()
		{
			if (info.trampoline) {
				static std::once_flag once;
				std::call_once(once, [&]() {
					if (!info.trampolineSize) {
						const auto hookStore = REL::HookStore::GetSingleton();
						info.trampolineSize += hookStore->GetSizeTrampoline();
					}

					auto& trampoline = REL::GetTrampoline();
					if (const auto intfc = GetTrampolineInterface()) {
						if (const auto mem = intfc->AllocateFromBranchPool(info.trampolineSize))
							trampoline.set_trampoline(mem, info.trampolineSize);
						else
							trampoline.create(info.trampolineSize);
					}
				});
			}
		}

		void API::InitHook(REL::HOOK_STEP a_step)
		{
			if (info.hook) {
				const auto hookStore = REL::HookStore::GetSingleton();
				hookStore->Init();
				hookStore->Enable(a_step);
			}
		}
	}

	void Init(const PreLoadInterface* a_intfc, InitInfo a_info) noexcept
	{
		static std::once_flag once;
		std::call_once(once, [&]() {
			auto api = Impl::API::GetSingleton();
			api->Init(a_info, a_intfc);
			api->InitLog();

			api->trampolineInterface = a_intfc->QueryInterface<TrampolineInterface>(PreLoadInterface::kTrampoline);

			api->InitTrampoline();
			api->InitHook(REL::HOOK_STEP::PRELOAD);
		});
	}

	void Init(const LoadInterface* a_intfc, InitInfo a_info) noexcept
	{
		static std::once_flag once;
		std::call_once(once, [&]() {
			auto api = Impl::API::GetSingleton();
			api->Init(a_info, a_intfc);
			api->InitLog();

			api->messagingInterface = a_intfc->QueryInterface<MessagingInterface>(LoadInterface::kMessaging);
			api->trampolineInterface = a_intfc->QueryInterface<TrampolineInterface>(LoadInterface::kTrampoline);

			api->InitTrampoline();
			api->InitHook(REL::HOOK_STEP::LOAD);
		});
	}

	OBSE::Version GetOBSEVersion() noexcept
	{
		return Impl::API::GetSingleton()->obse64Version;
	}

	std::string_view GetPluginName() noexcept
	{
		return Impl::API::GetSingleton()->pluginName;
	}

	std::string_view GetPluginAuthor() noexcept
	{
		return Impl::API::GetSingleton()->pluginAuthor;
	}

	OBSE::Version GetPluginVersion() noexcept
	{
		return Impl::API::GetSingleton()->pluginVersion;
	}

	PluginHandle GetPluginHandle() noexcept
	{
		return Impl::API::GetSingleton()->pluginHandle;
	}

	const PluginInfo* GetPluginInfo(std::string_view a_plugin) noexcept
	{
		if (const auto& accessor = Impl::API::GetSingleton()->pluginInfoAccessor) {
			if (const auto result = accessor(a_plugin.data())) {
				return static_cast<const PluginInfo*>(result);
			}
		}

		REX::ERROR("failed to get plugin info for {}", a_plugin);

		return nullptr;
	}

	std::uint32_t GetReleaseIndex() noexcept
	{
		return Impl::API::GetSingleton()->releaseIndex;
	}

	std::string_view GetSaveFolderName() noexcept
	{
		return Impl::API::GetSingleton()->saveFolderName;
	}

	const MessagingInterface* GetMessagingInterface() noexcept
	{
		return Impl::API::GetSingleton()->messagingInterface;
	}

	const TrampolineInterface* GetTrampolineInterface() noexcept
	{
		return Impl::API::GetSingleton()->trampolineInterface;
	}
}
