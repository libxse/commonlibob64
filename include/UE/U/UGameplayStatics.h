#pragma once

#include "UE/T/TPayload.h"
#include "UE/U/UBlueprintFunctionLibrary.h"

namespace UE
{
	class APlayerController;
	class UObject;

	class UGameplayStatics :
		public UBlueprintFunctionLibrary
	{
	public:
		UE_DEFINE_UOBJECT(UGameplayStatics, UBlueprintFunctionLibrary, "Engine", "GameplayStatics");

		// override
		virtual ~UGameplayStatics();  // 00

		static APlayerController* GetPlayerController(const UObject* a_object, std::int32_t a_playerIndex)
		{
			using func_t = decltype(&UGameplayStatics::GetPlayerController);
			static REL::Relocation<func_t> func{ ID::UGameplayStatics::GetPlayerController };
			return func(a_object, a_playerIndex);
		}

		static AActor* BeginDeferredActorSpawnFromClass(const UObject* a_object, UClass* a_class, const FTransform& a_transform, ESpawnActorCollisionHandlingMethod a_collision, AActor* a_owner, ESpawnActorScaleMethod a_scale)
		{
			TPayload<decltype(BeginDeferredActorSpawnFromClass)> payload{ a_object, a_class, a_transform, a_collision, a_owner, a_scale };

			const auto cls = FindClass<CLASS>();
			cls->ProcessEvent(cls->FindFunctionByName("BeginDeferredActorSpawnFromClass"), &payload);
			return payload.GetResult();
		}

		static AActor* FinishSpawningActor(AActor* a_actor, const FTransform& a_transform, ESpawnActorScaleMethod a_scale)
		{
			TPayload<decltype(FinishSpawningActor)> payload{ a_actor, a_transform, a_scale };

			const auto cls = FindClass<CLASS>();
			cls->ProcessEvent(cls->FindFunctionByName("FinishSpawningActor"), &payload);
			return payload.GetResult();
		}
	};
	static_assert(sizeof(UGameplayStatics) == 0x28);
}
