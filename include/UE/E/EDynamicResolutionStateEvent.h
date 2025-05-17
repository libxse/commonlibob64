#pragma once

namespace UE
{
    enum class EDynamicResolutionStateEvent : std::uint8_t
    {
        BeginFrame,
        BeginDynamicResolutionRendering,
        EndDynamicResolutionRendering,
        EndFrame
    };
}
