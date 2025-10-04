#pragma once

namespace UE
{
	class FDelegateHandle
	{
	public:
		enum EGenerateNewHandle
		{
			GenerateNewHandle
		};

		FDelegateHandle() = default;

		FDelegateHandle(EGenerateNewHandle) :
			m_id(GenerateNewID())
		{}

		bool IsValid() const
		{
			return m_id != 0;
		}

		bool operator==(const FDelegateHandle& a_rhs) const
		{
			return m_id == a_rhs.m_id;
		}

		bool operator!=(const FDelegateHandle& a_rhs) const
		{
			return m_id != a_rhs.m_id;
		}

	private:
		static std::uint64_t GenerateNewID()
		{
			using func_t = decltype(&FDelegateHandle::GenerateNewID);
			static REL::Relocation<func_t> func{ ID::FDelegateHandle::GenerateNewID };
			return func();
		}

	private:
		std::uint64_t m_id{ 0 };  // 000
	};
	static_assert(sizeof(FDelegateHandle) == 0x008);
}
