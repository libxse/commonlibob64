#pragma once

#include "UE/F/FVector.h"

namespace UE
{
	class FVector_NetQuantize10 :
		public FVector
	{
	public:
		FVector_NetQuantize10() = default;
	};

	class FVector_NetQuantize100 :
		public FVector
	{
	public:
		FVector_NetQuantize100() = default;
	};

	class FVector_NetQuantizeNormal :
		public FVector
	{
	public:
		FVector_NetQuantizeNormal() = default;
	};
}
