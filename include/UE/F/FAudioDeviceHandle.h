#pragma once

#include "UE/T/TWeakObjectPtr.h"

namespace UE::Audio
{
    using FDeviceId = std::uint32_t;
}

namespace UE
{
	class FAudioDevice;

    class FAudioDeviceHandle
    {
    public:
        // members
        TWeakObjectPtr<UWorld> world;     // 00
        FAudioDevice*          device;    // 08
        Audio::FDeviceId       deviceId;  // 10
    };
	static_assert(sizeof(FAudioDeviceHandle) == 0x18);
}
