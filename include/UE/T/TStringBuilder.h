#pragma once

#include "UE/F/FMemory.h"

namespace UE::StringBuilder::Private
{
	inline std::uint64_t NextPowerOfTwo(std::uint64_t a_value)
	{
		a_value -= 1;
		a_value |= (a_value >> 1);
		a_value |= (a_value >> 2);
		a_value |= (a_value >> 4);
		a_value |= (a_value >> 8);
		a_value |= (a_value >> 16);

		return a_value + 1;
	}
}

namespace UE
{
	template <class T>
	class TStringBuilderBase
	{
	public:
		static inline T EmptyBuffer[1]{};

		TStringBuilderBase() = default;

		TStringBuilderBase(T* a_base, std::int32_t a_capacity) :
			base(a_base), curPos(a_base), end(base + a_capacity)
		{}

		~TStringBuilderBase()
		{
			if (dynamic) {
				FreeBuffer(base, static_cast<std::size_t>(end - base));
			}
		}

		std::int32_t Len() const
		{
			return std::int32_t(curPos - base);
		}

		void EnsureAdditionalCapacity(std::int32_t a_capacity)
		{
			if ((curPos + a_capacity) < end)
				return;

			Extend(a_capacity);
		}

		void Extend(std::size_t a_capacity)
		{
			const std::size_t oldCapacity = end - base;
			const std::size_t newCapacity = std::max<std::size_t>(StringBuilder::Private::NextPowerOfTwo(oldCapacity + a_capacity), 32);

			T* newBase = (T*)AllocBuffer(newCapacity);

			std::size_t pos = curPos - base;
			FMemory::Memcpy(newBase, base, pos * sizeof(T));

			if (dynamic)
				FreeBuffer(base, oldCapacity);

			base = newBase;
			curPos = newBase + pos;
			end = newBase + newCapacity;
			dynamic = true;
		}

		void* AllocBuffer(std::size_t a_count)
		{
			return FMemory::Malloc(a_count * sizeof(T));
		}

		void FreeBuffer(void* a_buffer, std::size_t)
		{
			FMemory::Free(a_buffer);
		}

		// members
		T*   base{ EmptyBuffer };
		T*   curPos{ base };
		T*   end{ base + 1 };
		bool dynamic{ false };
	};
	static_assert(sizeof(TStringBuilderBase<char>) == 0x20);
	static_assert(sizeof(TStringBuilderBase<wchar_t>) == 0x20);

	template <class T>
	inline constexpr std::int32_t GetNum(const TStringBuilderBase<T>& a_builder)
	{
		return a_builder.Len();
	}

	template <class T, std::int32_t N>
	class TStringBuilderWithBuffer :
		public TStringBuilderBase<T>
	{
	public:
		TStringBuilderWithBuffer() :
			TStringBuilderBase<T>(stringBuffer, N)
		{}

	private:
		T stringBuffer[N];
	};

	template <std::int32_t N>
	using TStringBuilder = TStringBuilderWithBuffer<wchar_t, N>;
}
