#pragma once

namespace UE
{
	class FInputBindingHandle
	{
	public:
		virtual ~FInputBindingHandle() = default;  // 000

		FInputBindingHandle()
		{
			// TODO: m_handle = GInputBindingHandle++;
		}

		bool operator==(const FInputBindingHandle& a_rhs) const
		{
			return (m_handle == a_rhs.m_handle);
		}

	private:
		std::uint32_t m_handle{ 0 };  // 008
	};
	static_assert(sizeof(FInputBindingHandle) == 0x10);
}
