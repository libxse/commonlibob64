#pragma once

#include "UE/T/TSharedPtr.h"

namespace UE
{
	class FString;
	class FTextHistory;

	using FTextConstDisplayStringPtr = TSharedPtr<const FString, ESPMode::ThreadSafe>;

	class ITextData
	{
	public:
		// add
		virtual ~ITextData() = default;  // 00

		// add
		virtual const FString&             GetSourceString() const = 0;           // 01
		virtual const FString&             GetDisplayString() const = 0;          // 02
		virtual FTextConstDisplayStringPtr GetLocalizedString() const = 0;        // 03
		virtual std::uint16_t              GetGlobalHistoryRevision() const = 0;  // 04
		virtual std::uint16_t              GetLocalHistoryRevision() const = 0;   // 05
		virtual const FTextHistory&        GetTextHistory() const = 0;            // 06
		virtual FTextHistory&              GetMutableTextHistory() = 0;           // 07
	};
	static_assert(sizeof(ITextData) == 0x8);
}
