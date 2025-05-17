#pragma once

#include "UE/E/ETextFlag.h"
#include "UE/F/FName.h"
#include "UE/F/FString.h"
#include "UE/I/ITextData.h"
#include "UE/T/TSharedRef.h"

namespace UE
{
	class FText
	{
	public:
		FText() :
			textData(FText::GetEmpty().textData)
		{}

		// compiler doesn't see Relocation call as initializing textData, so use an empty FName
		explicit FText(FString&& a_str) :
			textData(FText::GetEmpty().textData)
		{
			using func_t = void (FText::*)(FString&&);
			static REL::Relocation<func_t> func{ ID::FText::Ctor1 };
			func(this, MoveTemp(a_str));
		}

		bool IsEmpty() const
		{
			return ToString().IsEmpty();
		}

		void Rebuild() const
		{
			using func_t = decltype(&FText::Rebuild);
			static REL::Relocation<func_t> func{ ID::FText::Rebuild };
			return func(this);
		}

		const FString& ToString() const
		{
			Rebuild();
			return textData->GetDisplayString();
		}

		static FText AsCultureInvariant(const FString& a_str)
		{
			FText text = a_str.IsEmpty() ? FText::GetEmpty() : FText(CopyTemp(a_str));
			text.flags |= ETextFlag::CultureInvariant;

			return text;
		}

		static FText AsCultureInvariant(FString&& a_str)
		{
			FText text = a_str.IsEmpty() ? FText::GetEmpty() : FText(MoveTemp(a_str));
			text.flags |= ETextFlag::CultureInvariant;

			return text;
		}

		static FText FromName(const FName& a_name)
		{
			return FText::FromString(a_name.ToString());
		}

		static FText FromString(const FString& a_str)
		{
			FText text = a_str.IsEmpty() ? FText::GetEmpty() : FText(CopyTemp(a_str));

			text.flags |= ETextFlag::InitializedFromString;

			return text;
		}

		static FText FromString(FString&& a_str)
		{
			FText text = a_str.IsEmpty() ? FText::GetEmpty() : FText(MoveTemp(a_str));

			text.flags |= ETextFlag::InitializedFromString;

			return text;
		}

		static const FText& GetEmpty()
		{
			using func_t = decltype(&FText::GetEmpty);
			static REL::Relocation<func_t> func{ ID::FText::GetEmpty };
			return func();
		}

		// members
		TSharedRef<ITextData> textData;    // 00
		ETextFlag             flags{ 0 };  // 10
	};
	static_assert(sizeof(FText) == 0x18);
}
