#pragma once

#include "UE/F/FMemory.h"

namespace RE
{
	inline void* malloc(std::size_t a_size)
	{
		return UE::FMemory::Malloc(a_size, 0x10);
	}

	template <class T>
	inline T* malloc(std::size_t a_size)
	{
		return static_cast<T*>(malloc(a_size));
	}

	template <class T>
	inline T* malloc()
	{
		return malloc<T>(sizeof(T));
	}

	inline void* aligned_alloc(std::uint32_t a_alignment, std::size_t a_size)
	{
		return UE::FMemory::Malloc(a_size, a_alignment);
	}

	template <class T>
	inline T* aligned_alloc(std::uint32_t a_alignment, std::size_t a_size)
	{
		return static_cast<T*>(aligned_alloc(a_alignment, a_size));
	}

	template <class T>
	inline T* aligned_alloc()
	{
		return aligned_alloc<T>(alignof(T), sizeof(T));
	}

	inline void* calloc(std::size_t a_num, std::size_t a_size)
	{
		const auto ret = malloc(a_num * a_size);
		if (ret) {
			std::memset(ret, 0, a_num * a_size);
		}
		return ret;
	}

	template <class T>
	inline T* calloc(std::size_t a_num, std::size_t a_size)
	{
		return static_cast<T*>(calloc(a_num, a_size));
	}

	template <class T>
	inline T* calloc(std::size_t a_num)
	{
		return calloc<T>(a_num, sizeof(T));
	}

	inline void* realloc(void* a_ptr, std::size_t a_newSize)
	{
		return UE::FMemory::Realloc(a_ptr, a_newSize, 0x10);
	}

	template <class T>
	inline T* realloc(void* a_ptr, std::size_t a_newSize)
	{
		return static_cast<T*>(realloc(a_ptr, a_newSize));
	}

	inline void* aligned_realloc(void* a_ptr, std::size_t a_newSize, std::uint32_t a_alignment)
	{
		return UE::FMemory::Realloc(a_ptr, a_newSize, a_alignment);
	}

	template <class T>
	inline T* aligned_realloc(void* a_ptr, std::size_t a_newSize, std::uint32_t a_alignment)
	{
		return static_cast<T*>(aligned_realloc(a_ptr, a_newSize, a_alignment));
	}

	inline void free(void* a_ptr)
	{
		if (a_ptr) {
			UE::FMemory::Free(a_ptr);
		}
	}
}

#define TES4_DEFINE_NEW()                                                                                               \
	[[nodiscard]] inline void* operator new(std::size_t a_count)                                                        \
	{                                                                                                                   \
		const auto mem = RE::malloc(a_count);                                                                           \
		if (!mem) {                                                                                                     \
			REX::FAIL("out of memory");                                                                                 \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] inline void* operator new[](std::size_t a_count)                                                      \
	{                                                                                                                   \
		const auto mem = RE::malloc(a_count);                                                                           \
		if (!mem) {                                                                                                     \
			REX::FAIL("out of memory");                                                                                 \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] constexpr void* operator new(std::size_t, void* a_ptr) noexcept { return a_ptr; }                     \
	[[nodiscard]] constexpr void* operator new[](std::size_t, void* a_ptr) noexcept { return a_ptr; }                   \
	[[nodiscard]] constexpr void* operator new(std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; }   \
	[[nodiscard]] constexpr void* operator new[](std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; } \
                                                                                                                        \
	inline void operator delete(void* a_ptr) { RE::free(a_ptr); }                                                       \
	inline void operator delete[](void* a_ptr) { RE::free(a_ptr); }                                                     \
	inline void operator delete(void* a_ptr, std::size_t) { RE::free(a_ptr); }                                          \
	inline void operator delete[](void* a_ptr, std::size_t) { RE::free(a_ptr); }
