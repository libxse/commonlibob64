#pragma once

#include "REL/Relocation.h"

#define OBSEAPI __cdecl

namespace OBSE
{
	using PluginHandle = std::uint32_t;

	namespace Impl
	{
		struct OBSEInterface
		{
			std::uint32_t obse64Version;
			std::uint32_t runtimeVersion;
			std::uint32_t editorVersion;
			std::uint32_t isEditor;
			std::uint32_t interfaceVersion;
			void*(OBSEAPI* QueryInterface)(std::uint32_t);
			std::uint32_t(OBSEAPI* GetPluginHandle)(void);
			std::uint32_t(OBSEAPI* GetReleaseIndex)(void);
			const void*(OBSEAPI* GetPluginInfo)(const char*);
			const char*(OBSEAPI* GetSaveFolderName)(void);
		};

		struct OBSEMessagingInterface
		{
			std::uint32_t interfaceVersion;
			bool(OBSEAPI* RegisterListener)(std::uint32_t, const char*, void*);
			bool(OBSEAPI* Dispatch)(std::uint32_t, std::uint32_t, void*, std::uint32_t, const char*);
		};

		struct OBSETrampolineInterface
		{
			std::uint32_t interfaceVersion;
			void*(OBSEAPI* AllocateFromBranchPool)(std::uint32_t, std::size_t);
			void*(OBSEAPI* AllocateFromLocalPool)(std::uint32_t, std::size_t);
		};
	}

	class QueryInterface
	{
	protected:
		[[nodiscard]] decltype(auto) GetProxy() const noexcept
		{
			return reinterpret_cast<const Impl::OBSEInterface&>(*this);
		}

	private:
		[[nodiscard]] constexpr static OBSE::Version MakeVersion(std::uint32_t a_version) noexcept
		{
			return {
				static_cast<std::uint16_t>((a_version >> 28) & 0x00F),
				static_cast<std::uint16_t>((a_version >> 16) & 0xFFF),
				static_cast<std::uint16_t>((a_version >> 4) & 0xFFF),
				static_cast<std::uint16_t>((a_version >> 0) & 0x00F)
			};
		}

	public:
		[[nodiscard]] OBSE::Version    EditorVersion() const noexcept { return MakeVersion(GetProxy().editorVersion); }
		[[nodiscard]] PluginHandle     GetPluginHandle() const { return GetProxy().GetPluginHandle(); }
		[[nodiscard]] std::uint32_t    GetReleaseIndex() const { return GetProxy().GetReleaseIndex(); }
		[[nodiscard]] std::string_view GetSaveFolderName() const { return GetProxy().GetSaveFolderName(); }
		[[nodiscard]] OBSE::Version    InterfaceVersion() const noexcept { return MakeVersion(GetProxy().interfaceVersion); }
		[[nodiscard]] bool             IsEditor() const noexcept { return GetProxy().isEditor != 0; }
		[[nodiscard]] OBSE::Version    OBSEVersion() const noexcept { return MakeVersion(GetProxy().obse64Version); }
		[[nodiscard]] OBSE::Version    RuntimeVersion() const noexcept { return MakeVersion(GetProxy().runtimeVersion); }
	};

	class PreLoadInterface :
		public QueryInterface
	{
	public:
		enum : std::uint32_t
		{
			kInvalid = 0,
			kTrampoline = 2
		};

		[[nodiscard]] void* QueryInterface(std::uint32_t a_id) const { return GetProxy().QueryInterface(a_id); }

		template <class T>
		T* QueryInterface(std::uint32_t a_id) const noexcept
		{
			auto result = static_cast<T*>(QueryInterface(a_id));
			if (result && result->Version() > T::kVersion)
				REX::ERROR("interface definition is out of date");

			return result;
		}
	};

	class LoadInterface :
		public QueryInterface
	{
	public:
		enum : std::uint32_t
		{
			kInvalid = 0,
			kMessaging = 1,
			kTrampoline = 2,
		};

		[[nodiscard]] void* QueryInterface(std::uint32_t a_id) const { return GetProxy().QueryInterface(a_id); }

		template <class T>
		T* QueryInterface(std::uint32_t a_id) const noexcept
		{
			auto result = static_cast<T*>(QueryInterface(a_id));
			if (result && result->Version() > T::kVersion)
				REX::ERROR("interface definition is out of date");

			return result;
		}
	};

	class MessagingInterface
	{
	private:
		[[nodiscard]] decltype(auto) GetProxy() const noexcept
		{
			return reinterpret_cast<const Impl::OBSEMessagingInterface&>(*this);
		}

	public:
		enum : std::uint32_t
		{
			kVersion = 1
		};

		enum : std::uint32_t
		{
			kPostLoad,
			kPostPostLoad,
			kDataLoaded
		};

		struct Message
		{
			const char*   sender;
			std::uint32_t type;
			std::uint32_t dataLen;
			void*         data;
		};

		using EventCallback = void OBSEAPI(Message* a_msg);

		[[nodiscard]] std::uint32_t Version() const noexcept { return GetProxy().interfaceVersion; }

		bool RegisterListener(EventCallback* a_handler) const { return RegisterListener(a_handler, "OBSE"sv); }
		bool RegisterListener(EventCallback* a_handler, std::string_view a_sender) const;
		bool Dispatch(std::uint32_t a_messageType, void* a_data, std::uint32_t a_dataLen, const char* a_receiver) const;
	};

	class TrampolineInterface
	{
	private:
		[[nodiscard]] decltype(auto) GetProxy() const noexcept
		{
			return reinterpret_cast<const Impl::OBSETrampolineInterface&>(*this);
		}

	public:
		enum
		{
			kVersion = 1
		};

		[[nodiscard]] std::uint32_t Version() const noexcept { return GetProxy().interfaceVersion; }
		[[nodiscard]] void*         AllocateFromBranchPool(std::size_t a_size) const;
		[[nodiscard]] void*         AllocateFromLocalPool(std::size_t a_size) const;
	};

	struct PluginInfo
	{
		enum : std::uint32_t
		{
			kVersion = 1
		};

		std::uint32_t infoVersion;
		const char*   name;
		std::uint32_t version;
	};

	struct PluginVersionData
	{
	public:
		enum Version : std::uint32_t
		{
			kVersion = 1
		};

		enum
		{
			kAddressIndependence_Signatures = 1 << 0,
			kAddressIndependence_AddressLibrary = 1 << 1,
		};

		enum
		{
			kStructureIndependence_NoStructs = 1 << 0,
			kStructureIndependence_InitialLayout = 1 << 1,
		};

		constexpr void PluginVersion(const OBSE::Version a_version) noexcept { pluginVersion = a_version.pack(); }

		[[nodiscard]] constexpr OBSE::Version GetPluginVersion() const noexcept { return OBSE::Version::unpack(pluginVersion); }

		constexpr void PluginName(const std::string_view a_plugin) noexcept { SetCharBuffer(a_plugin, std::span{ pluginName }); }

		[[nodiscard]] constexpr std::string_view GetPluginName() const noexcept { return std::string_view{ pluginName }; }

		constexpr void AuthorName(const std::string_view a_name) noexcept { SetCharBuffer(a_name, std::span{ author }); }

		[[nodiscard]] constexpr std::string_view GetAuthorName() const noexcept { return std::string_view{ author }; }

		constexpr void UsesSigScanning(const bool a_value) noexcept { SetOrClearBit(addressIndependence, kAddressIndependence_Signatures, a_value); }

		constexpr void UsesAddressLibrary(const bool a_value) noexcept { SetOrClearBit(addressIndependence, kAddressIndependence_AddressLibrary, a_value); }

		constexpr void HasNoStructUse(const bool a_value) noexcept { SetOrClearBit(structureIndependence, kStructureIndependence_NoStructs, a_value); }

		constexpr void IsLayoutDependent(const bool a_value) noexcept { SetOrClearBit(structureIndependence, kStructureIndependence_InitialLayout, a_value); }

		constexpr void CompatibleVersions(std::initializer_list<OBSE::Version> a_versions) noexcept
		{
			// must be zero-terminated
			assert(a_versions.size() < std::size(compatibleVersions) - 1);
			std::ranges::transform(a_versions, std::begin(compatibleVersions), [](const OBSE::Version& a_version) noexcept {
				return a_version.pack();
			});
		}

		constexpr void MinimumRequiredXSEVersion(const OBSE::Version a_version) noexcept { xseMinimum = a_version.pack(); }

		[[nodiscard]] static const PluginVersionData* GetSingleton() noexcept;

		const std::uint32_t dataVersion{ kVersion };
		std::uint32_t       pluginVersion = 0;
		char                pluginName[256] = {};
		char                author[256] = {};
		std::uint32_t       addressIndependence;
		std::uint32_t       structureIndependence;
		std::uint32_t       compatibleVersions[16] = {};
		std::uint32_t       xseMinimum = 0;
		const std::uint32_t reservedNonBreaking = 0;
		const std::uint32_t reservedBreaking = 0;
		const std::uint8_t  reserved[512] = {};

	private:
		static constexpr void SetCharBuffer(std::string_view a_src, std::span<char> a_dst) noexcept
		{
			assert(a_src.size() < a_dst.size());
			std::ranges::fill(a_dst, '\0');
			std::ranges::copy(a_src, a_dst.begin());
		}

		static constexpr void SetOrClearBit(std::uint32_t& a_data, const std::uint32_t a_bit, const bool a_set) noexcept
		{
			if (a_set)
				a_data |= a_bit;
			else
				a_data &= ~a_bit;
		}
	};

	static_assert(offsetof(PluginVersionData, dataVersion) == 0x000);
	static_assert(offsetof(PluginVersionData, pluginVersion) == 0x004);
	static_assert(offsetof(PluginVersionData, pluginName) == 0x008);
	static_assert(offsetof(PluginVersionData, author) == 0x108);
	static_assert(offsetof(PluginVersionData, addressIndependence) == 0x208);
	static_assert(offsetof(PluginVersionData, structureIndependence) == 0x20C);
	static_assert(offsetof(PluginVersionData, compatibleVersions) == 0x210);
	static_assert(offsetof(PluginVersionData, xseMinimum) == 0x250);
	static_assert(offsetof(PluginVersionData, reservedNonBreaking) == 0x254);
	static_assert(offsetof(PluginVersionData, reservedBreaking) == 0x258);
	static_assert(offsetof(PluginVersionData, reserved) == 0x25C);
	static_assert(sizeof(PluginVersionData) == 0x45C);
}

#define OBSE_EXPORT extern "C" [[maybe_unused]] __declspec(dllexport)
#define OBSE_PLUGIN_PRELOAD(...) OBSE_EXPORT bool OBSEPlugin_Preload(__VA_ARGS__)
#define OBSE_PLUGIN_LOAD(...) OBSE_EXPORT bool OBSEPlugin_Load(__VA_ARGS__)
#define OBSE_PLUGIN_VERSION OBSE_EXPORT constinit OBSE::PluginVersionData OBSEPlugin_Version
#define OBSEPluginPreload OBSE_PLUGIN_PRELOAD
#define OBSEPluginLoad OBSE_PLUGIN_LOAD
#define OBSEPluginVersion OBSE_PLUGIN_VERSION
