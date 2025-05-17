#pragma once

#include "UE/F/FString.h"

namespace UE
{
    class FDirectoryPath
    {
    public:
        // members
        FString path;  // 00
    };
    static_assert(sizeof(FDirectoryPath) == 0x10);
}
