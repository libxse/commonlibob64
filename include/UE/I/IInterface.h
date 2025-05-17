#pragma once

namespace UE
{
	class UInterface;

	class IInterface
	{
	public:
		using CLASS_TYPE = UInterface;

		virtual ~IInterface() = default;
	};
}
