#pragma once

#include "UE/T/TRotator.h"
#include "UE/T/TSubclassOf.h"
#include "UE/U/UObject.h"

namespace UE
{
	enum class ECollisionChannel : std::int32_t;

	class AActor;
	class ADebugCameraController;
	class APawn;
	class APlayerController;
	class FDebugTraceInfo;
	class FHitResult;
	class UCheatManagerExtension;

	class UCheatManager :
		public UObject
	{
	public:
		UE_DEFINE_UOBJECT(UCheatManager, UObject, "Engine", "CheatManager");

		// override
		virtual ~UCheatManager();  // 00

		// add
		virtual bool    ServerToggleAILogging_Validate();                                                        // 57
		virtual void    ServerToggleAILogging_Implementation();                                                  // 58
		virtual void    FreezeFrame(float);                                                                      // 59
		virtual void    Teleport();                                                                              // 5A
		virtual void    ChangeSize(float);                                                                       // 5B
		virtual void    Fly();                                                                                   // 5C
		virtual void    Walk();                                                                                  // 5D
		virtual void    Ghost();                                                                                 // 5E
		virtual void    God();                                                                                   // 5F
		virtual void    Slomo(float);                                                                            // 60
		virtual void    DamageTarget(float);                                                                     // 61
		virtual void    DestroyTarget();                                                                         // 62
		virtual void    DestroyAll(TSubclassOf<AActor>);                                                         // 63
		virtual void    DestroyAllPawnsExceptTarget();                                                           // 64
		virtual void    DestroyPawns(TSubclassOf<APawn>);                                                        // 65
		virtual void    Summon(const FString*);                                                                  // 66
		virtual void    PlayersOnly();                                                                           // 67
		virtual void    ViewSelf();                                                                              // 68
		virtual void    ViewPlayer(const FString*);                                                              // 69
		virtual void    ViewActor(FName);                                                                        // 6A
		virtual void    ViewClass(TSubclassOf<AActor>);                                                          // 6B
		virtual void    StreamLevelIn(FName);                                                                    // 6C
		virtual void    OnlyLoadLevel(FName);                                                                    // 6D
		virtual void    StreamLevelOut(FName);                                                                   // 6E
		virtual void    ToggleDebugCamera();                                                                     // 6F
		virtual void    ToggleAILogging();                                                                       // 70
		virtual void    ServerToggleAILogging();                                                                 // 71
		virtual void    DebugCapsuleSweep();                                                                     // 72
		virtual void    DebugCapsuleSweepSize(float, float);                                                     // 73
		virtual void    DebugCapsuleSweepChannel(ECollisionChannel);                                             // 74
		virtual void    DebugCapsuleSweepComplex(bool);                                                          // 75
		virtual void    DebugCapsuleSweepCapture();                                                              // 76
		virtual void    DebugCapsuleSweepPawn();                                                                 // 77
		virtual void    DebugCapsuleSweepClear();                                                                // 78
		virtual void    TestCollisionDistance();                                                                 // 79
		virtual void    DumpOnlineSessionState();                                                                // 7A
		virtual void    DumpPartyState();                                                                        // 7B
		virtual void    DumpChatState();                                                                         // 7C
		virtual void    DumpVoiceMutingState();                                                                  // 7D
		virtual void    BugItGo(float, float, float, float, float, float);                                       // 7E
		virtual void    BugItGoString(const FString*, const FString*);                                           // 7F
		virtual void    BugIt(const FString*);                                                                   // 80
		virtual void    BugItStringCreator(Math::TVector<double>, Math::TRotator<double>, FString*, FString*);   // 81
		virtual void    FlushLog();                                                                              // 82
		virtual void    LogLoc();                                                                                // 83
		virtual void    SetMouseSensitivityToDefault();                                                          // 84
		virtual void    InvertMouse();                                                                           // 85
		virtual void    BugItWorker(Math::TVector<double>, Math::TRotator<double>);                              // 86
		virtual void    LogOutBugItGoToLogFile(const FString*, const FString*, const FString*, const FString*);  // 87
		virtual void    SetLevelStreamingStatus(FName, bool, bool);                                              // 88
		virtual void    InitCheatManager();                                                                      // 89
		virtual bool    DoGameSpecificBugItLog(FOutputDevice*);                                                  // 8A
		virtual void    EnableDebugCamera();                                                                     // 8B
		virtual void    DisableDebugCamera();                                                                    // 8C
		virtual AActor* GetTarget(APlayerController*, FHitResult*);                                              // 8D

		// members
		TObjectPtr<ADebugCameraController>         debugCameraControllerRef;     // 028
		TSubclassOf<ADebugCameraController>        debugCameraControllerClass;   // 030
		std::uint32_t                              debugCapsuleSweep: 1;         // 038:0
		std::uint32_t                              debugCapsuleTraceComplex: 1;  // 038:1
		std::uint32_t                              toggleAILogging: 1;           // 038:2
		float                                      debugTraceDistance;           // 03C
		float                                      debugCapsuleHalfHeight;       // 040
		float                                      debugCapsuleRadius;           // 044
		float                                      debugTraceDrawNormalLength;   // 048
		TEnumAsByte<ECollisionChannel>             debugTraceChannel;            // 04C
		TArray<FDebugTraceInfo>                    debugTraceInfoList;           // 050
		TArray<FDebugTraceInfo>                    debugTracePawnInfoList;       // 060
		std::int32_t                               currentTraceIndex;            // 070
		std::int32_t                               currentTracePawnIndex;        // 074
		TArray<TObjectPtr<UCheatManagerExtension>> cheatManagerExtensions;       // 078
	};
	static_assert(sizeof(UCheatManager) == 0x88);
}
