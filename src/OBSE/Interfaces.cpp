#include "OBSE/Interfaces.h"

#include "OBSE/API.h"

#include "REX/W32/KERNEL32.h"

namespace OBSE
{
	bool MessagingInterface::RegisterListener(EventCallback* a_handler, std::string_view a_sender) const
	{
		const auto success = GetProxy().RegisterListener(GetPluginHandle(), a_sender.data(), reinterpret_cast<void*>(a_handler));
		if (!success) {
			REX::ERROR("failed to register listener for {}", a_sender);
		}
		return success;
	}

	bool MessagingInterface::Dispatch(std::uint32_t a_messageType, void* a_data, std::uint32_t a_dataLen, const char* a_receiver) const
	{
		const auto success = GetProxy().Dispatch(GetPluginHandle(), a_messageType, a_data, a_dataLen, a_receiver);
		if (!success) {
			REX::ERROR("failed to dispatch to {}", (a_receiver ? a_receiver : "all listeners"));
		}
		return success;
	}

	void* TrampolineInterface::AllocateFromBranchPool(std::size_t a_size) const
	{
		const auto mem = GetProxy().AllocateFromBranchPool(GetPluginHandle(), a_size);
		if (!mem) {
			REX::ERROR("failed to allocate from branch pool");
		}
		return mem;
	}

	void* TrampolineInterface::AllocateFromLocalPool(std::size_t a_size) const
	{
		const auto mem = GetProxy().AllocateFromLocalPool(GetPluginHandle(), a_size);
		if (!mem) {
			REX::ERROR("failed to allocate from local pool");
		}
		return mem;
	}

	const PluginVersionData* PluginVersionData::GetSingleton() noexcept
	{
		return reinterpret_cast<const PluginVersionData*>(REX::W32::GetProcAddress(REX::W32::GetCurrentModule(), "OBSEPlugin_Version"));
	}
}
