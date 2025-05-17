#pragma once

#include "UE/F/FMemory.h"
#include "UE/T/TAllocatorTraits.h"
#include "UE/T/TBitsToSizeType.h"

namespace UE
{
	class FMemory;
	class FScriptContainerElement;

	template <class T>
	inline T DefaultCalculateSlackGrow(T a_num, T a_numAlloc, std::size_t a_numBytes, bool a_allowQuantize, std::uint32_t a_alignment = 0)
	{
		T result;

		assert(a_num > a_numAlloc && a_num > 0);

		std::size_t grow = 4;
		std::size_t growConstant = 16;

		if (a_numAlloc) {
			grow = static_cast<std::size_t>(a_num) + 3 * static_cast<std::size_t>(a_num) / 8 + growConstant;
		} else if (static_cast<std::size_t>(a_num) > grow) {
			grow = static_cast<std::size_t>(a_num);
		}

		if (a_allowQuantize) {
			result = static_cast<T>(FMemory::QuantizeSize(grow * a_numBytes, a_alignment) / a_numBytes);
		} else {
			result = static_cast<T>(grow);
		}

		if (a_num > result)
			result = std::numeric_limits<T>::max();

		return result;
	}

	template <class T>
	inline T DefaultCalculateSlackReserve(T a_num, std::size_t a_numBytes, bool a_allowQuantize, std::uint32_t a_alignment = 0)
	{
		T result = a_num;

		assert(a_num > 0);

		if (a_allowQuantize) {
			result = static_cast<T>(FMemory::QuantizeSize(static_cast<std::size_t>(result) * static_cast<std::size_t>(a_numBytes), a_alignment) / a_numBytes);
			if (a_num > result)
				result = std::numeric_limits<T>::max();
		}

		return result;
	}

	template <class T>
	inline T DefaultCalculateSlackShrink(T a_num, T a_numAlloc, std::size_t a_numBytes, bool a_allowQuantize, std::uint32_t a_alignment = 0)
	{
		T result;

		assert(a_num < a_numAlloc);

		const T           slackElements = a_numAlloc - a_num;
		const std::size_t slackBytes = (a_numAlloc - a_num) * a_numBytes;
		if ((slackBytes >= 16384 || 3 * a_num < 2 * a_numAlloc) && (slackElements > 64 || !a_num)) {
			result = a_num;
			if (result > 0 && a_allowQuantize)
				result = (T)(FMemory::QuantizeSize(result * a_numBytes, a_alignment) / a_numBytes);
		} else {
			result = a_numAlloc;
		}

		return result;
	}

	template <std::int32_t N, class M = FMemory>
	class TSizedHeapAllocator
	{
	public:
		static constexpr bool NeedsElementType{ true };
		static constexpr bool RequireRangeCheck{ true };

		using SizeType = TBitsToSizeType<N>::Type;
		using USizeType = std::make_unsigned_t<SizeType>;

		class ForAnyElementType
		{
		public:
			ForAnyElementType() = default;

			~ForAnyElementType()
			{
				if (data)
					M::Free(data);
			}

			SizeType CalculateSlackReserve(SizeType a_num, std::size_t a_numBytes) const
			{
				return DefaultCalculateSlackReserve(a_num, a_numBytes, true);
			}

			SizeType CalculateSlackReserve(SizeType a_num, std::size_t a_numBytes, std::uint32_t a_alignment) const
			{
				return DefaultCalculateSlackReserve(a_num, a_numBytes, true, a_alignment);
			}

			SizeType CalculateSlackShrink(SizeType a_num, SizeType a_numAlloc, std::size_t a_numBytes) const
			{
				return DefaultCalculateSlackShrink(a_num, a_numAlloc, a_numBytes, true);
			}

			SizeType CalculateSlackShrink(SizeType a_num, SizeType a_numAlloc, std::size_t a_numBytes, std::uint32_t a_alignment) const
			{
				return DefaultCalculateSlackShrink(a_num, a_numAlloc, a_numBytes, true, a_alignment);
			}

			SizeType CalculateSlackGrow(SizeType a_num, SizeType a_numAlloc, std::size_t a_numBytes) const
			{
				return DefaultCalculateSlackGrow(a_num, a_numAlloc, a_numBytes, true);
			}

			SizeType CalculateSlackGrow(SizeType a_num, SizeType a_numAlloc, std::size_t a_numBytes, std::uint32_t a_alignment) const
			{
				return DefaultCalculateSlackGrow(a_num, a_numAlloc, a_numBytes, true, a_alignment);
			}

			FScriptContainerElement* GetAllocation() const
			{
				return data;
			}

			SizeType GetInitialCapacity() const
			{
				return 0;
			}

			bool HasAllocation() const
			{
				return data;
			}

			void ResizeAllocation(SizeType a_numPrevious, SizeType a_num, std::size_t a_numBytes)
			{
				if (data || a_num) {
					bool invalid = a_num < 0 || a_numBytes < 1 || a_numBytes > static_cast<std::size_t>(std::numeric_limits<std::int32_t>::max());

					if constexpr (sizeof(SizeType) == sizeof(std::size_t))
						invalid = invalid || (static_cast<std::size_t>(static_cast<USizeType>(a_num)) > static_cast<std::size_t>(std::numeric_limits<SizeType>::max()) / a_numBytes);

					assert(!invalid);

					data = static_cast<FScriptContainerElement*>(M::Realloc(data, a_num * a_numBytes));
				}
			}

			void ResizeAllocation(SizeType, SizeType a_num, std::size_t a_numBytes, std::uint32_t a_alignment)
			{
				if (data || a_num) {
					bool invalid = a_num < 0 || a_numBytes < 1 || a_numBytes > static_cast<std::size_t>(std::numeric_limits<std::int32_t>::max());

					if constexpr (sizeof(SizeType) == sizeof(std::size_t))
						invalid = invalid || (static_cast<std::size_t>(static_cast<USizeType>(a_num)) > static_cast<std::size_t>(std::numeric_limits<SizeType>::max()) / a_numBytes);

					assert(!invalid);

					data = static_cast<FScriptContainerElement*>(M::Realloc(data, a_num * a_numBytes, a_alignment));
				}
			}

			// members
			FScriptContainerElement* data{ nullptr };  // 00
		};
		static_assert(sizeof(ForAnyElementType) == 0x08);

		template <class T>
		class ForElementType :
			public ForAnyElementType
		{
		public:
			ForElementType() = default;

			T* GetAllocation() const
			{
				return reinterpret_cast<T*>(ForAnyElementType::GetAllocation());
			}
		};
		static_assert(sizeof(ForElementType<void*>) == 0x08);
	};
	static_assert(std::is_empty_v<TSizedHeapAllocator<32, FMemory>>);

	template <std::int32_t N>
	struct TAllocatorTraits<TSizedHeapAllocator<N>> :
		TAllocatorTraitsBase<TSizedHeapAllocator<N>>
	{
		static constexpr bool IsZeroConstruct{ true };
		static constexpr bool SupportsElementAlignment{ true };
	};

	using FHeapAllocator = TSizedHeapAllocator<32>;
}
