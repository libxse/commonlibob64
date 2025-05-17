#pragma once

namespace UE
{
    enum class ETransitionType : std::uint8_t
    {
        None = 0,
        Paused = 1,
        Loading = 2,
        Saving = 3,
        Connecting = 4,
        Precaching = 5,
        WaitingToConnect = 6
    };
}
