#pragma once

#include "UE/F/FSoftObjectPath.h"

namespace UE
{
	class FSoftClassPath :
		public FSoftObjectPath
	{
	public:
		FSoftClassPath() = default;
	};
	static_assert(sizeof(FSoftClassPath) == 0x20);
}
