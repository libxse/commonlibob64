#pragma once

namespace UE
{
	class FMemory
	{
	public:
		static void Free(void* a_ptr)
		{
			using func_t = decltype(&FMemory::Free);
			static REL::Relocation<func_t> func{ ID::FMemory::Free };
			func(a_ptr);
		}

		static void* Malloc(std::size_t a_size, std::uint32_t a_alignment = 0)
		{
			using func_t = decltype(&FMemory::Malloc);
			static REL::Relocation<func_t> func{ ID::FMemory::Malloc };
			return func(a_size, a_alignment);
		}

		static void* Realloc(void* a_ptr, std::size_t a_size, std::uint32_t a_alignment = 0)
		{
			using func_t = decltype(&FMemory::Realloc);
			static REL::Relocation<func_t> func{ ID::FMemory::Realloc };
			return func(a_ptr, a_size, a_alignment);
		}

		static void* Memcpy(void* a_dst, const void* a_src, std::size_t a_size)
		{
			return std::memcpy(a_dst, a_src, a_size);
		}

		template <class T>
		static void Memcpy(T& a_dst, const T& a_src)
		{
			Memcpy(&a_dst, &a_src, sizeof(T));
		}

		static std::size_t QuantizeSize(std::size_t a_count, std::uint32_t a_alignment = 0)
		{
			using func_t = decltype(&FMemory::QuantizeSize);
			static REL::Relocation<func_t> func{ ID::FMemory::QuantizeSize };
			return func(a_count, a_alignment);
		}
	};
}
