#pragma once

#include "UE/T/TPayload.h"
#include "UE/U/UBlueprintFunctionLibrary.h"
#include "UE/U/UClass.h"

namespace UE
{
	class UKismetSystemLibrary :
		public UBlueprintFunctionLibrary
	{
	public:
		UE_DEFINE_UOBJECT(UKismetSystemLibrary, UBlueprintFunctionLibrary, "Engine", "KismetSystemLibrary");

		// override
		virtual ~UKismetSystemLibrary();  // 00

		static FString GetGameName()
		{
			TPayload<decltype(GetGameName)> payload;

			const auto cls = FindClass<CLASS>();
			cls->ProcessEvent(cls->FindFunctionByName("GetGameName"), &payload);
			return payload.GetResult();
		}

		static FString GetObjectName(const UObject* a_object)
		{
			TPayload<decltype(GetObjectName)> payload{ a_object };

			const auto cls = FindClass<CLASS>();
			cls->ProcessEvent(cls->FindFunctionByName("GetObjectName"), &payload);
			return payload.GetResult();
		}

		static FString GetPathName(const UObject* a_object)
		{
			TPayload<decltype(GetPathName)> payload{ a_object };

			const auto cls = FindClass<CLASS>();
			cls->ProcessEvent(cls->FindFunctionByName("GetPathName"), &payload);
			return payload.GetResult();
		}
	};
}
