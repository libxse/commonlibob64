#pragma once

#include "UE/A/AActor.h"
#include "UE/I/INavAgentInterface.h"
#include "UE/T/TBaseDynamicMulticastDelegate.h"
#include "UE/T/TMulticastDelegate.h"

namespace UE
{
	class ACharacter;
	class APawn;
	class APlayerState;
	class UDamageType;

	using FInstigatedAnyDamageSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, float, const UDamageType*, AActor*, AActor*>;
	using FOnPossessedPawnChanged = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, APawn*, APawn*>;
	using FPawnChangedSignature = TMulticastDelegate<void(APawn*)>;

	class AController :
		public AActor,
		public INavAgentInterface
	{
	public:
		UE_DEFINE_UOBJECT(AController, AActor, "Engine", "Controller");

		// override
		virtual ~AController();

		// members
		TObjectPtr<APlayerState>      playerState;                    // 2A0
		TWeakObjectPtr<AActor>        startSpot;                      // 2A8
		FInstigatedAnyDamageSignature onInstigatedAnyDamage;          // 2B0
		FOnPossessedPawnChanged       onPossessedPawnChanged;         // 2C0
		FName                         stateName;                      // 2D0
		TObjectPtr<APawn>             pawn;                           // 2D8
		TWeakObjectPtr<APawn>         oldPawn;                        // 2E0
		TObjectPtr<ACharacter>        character;                      // 2E8
		TObjectPtr<USceneComponent>   transformComponent;             // 2F0
		FPawnChangedSignature         onNewPawn;                      // 2F8
		FRotator                      controlRotation;                // 310
		std::uint8_t                  attachToPawn: 1;                // 328:0
		std::uint8_t                  isPlayerController: 1;          // 328:1
		std::uint8_t                  canPossessWithoutAuthority: 1;  // 328:2
		std::uint8_t                  ignoreMoveInput;                // 329
		std::uint8_t                  ignoreLookInput;                // 330
	};
	static_assert(sizeof(AController) == 0x330);
}
