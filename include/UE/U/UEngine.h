#pragma once

#include "UE/E/EDynamicResolutionStateEvent.h"
#include "UE/E/EFrameHitchType.h"
#include "UE/E/ETransitionType.h"
#include "UE/F/FAudioDeviceHandle.h"
#include "UE/F/FColor.h"
#include "UE/F/FDirectoryPath.h"
#include "UE/F/FExec.h"
#include "UE/F/FFrameRate.h"
#include "UE/F/FScreenMessageString.h"
#include "UE/F/FSoftClassPath.h"
#include "UE/F/FObjectSubsystemCollection.h"
#include "UE/F/FVector.h"
#include "UE/F/FVector2.h"
#include "UE/F/FURL.h"
#include "UE/T/TSharedPtr.h"
#include "UE/U/UObject.h"

namespace UE
{
	namespace EBrowseReturnVal
	{
		enum class Type : std::int32_t;
	}

	namespace ENetworkFailure
	{
		enum class Type : std::int32_t;
	}

	namespace ENetworkLagState
	{
		enum class Type : std::int32_t;
	}

	namespace ERHIFeatureLevel
	{
		enum class Type : std::int32_t;
	}

	namespace ETravelFailure
	{
		enum class Type : std::int32_t;
	}

	enum class EGarbageCollectionType : std::int8_t;

	class AActor;
	class ALevelScriptActor;
	class AWorldSettings;
	class FAnalyticsEventAttribute;
	class FAudioDeviceManager;
	class FCanvas;
	class FClassRedirect;
	class FColor;
	class FCommonViewportClient;
	class FDropNoteInfo;
	class FGameNameRedirect;
	class FIrisNetDriverConfig;
	class FNetDriverDefinition;
	class FPerformanceTrackingChart;
	class FPluginRedirect;
	class FRDGBuilder;
	class FRunnableThread;
	class FSceneViewExtensions;
	class FScreenSaverInhibitor;
	class FStatColorMapping;
	class FStructRedirect;
	class FTypeContainer;
	class FViewport;
	class FWorldContext;
	class IDynamicResolutionState;
	class IEngineLoop;
	class IEyeTracker;
	class IMessageRpcClient;
	class IPerformanceDataConsumer;
	class IPortalRpcLocator;
	class IPortalServiceLocator;
	class IStereoRendering;
	class IXRTrackingSystem;
	class SViewport;
	class UAssetManager;
	class UAvoidanceManager;
	class UConsole;
	class UEngineCustomTimeStep;
	class UEngineSubsystem;
	class UFont;
	class UGameUserSettings;
	class UGameViewportClient;
	class ULocalPlayer;
	class UMaterial;
	class UMaterialInstanceDynamic;
	class UNavigationSystemBase;
	class UNavigationSystemConfig;
	class UNetConnection;
	class UNetDriver;
	class UPendingNetGame;
	class UPhysicalMaterial;
	class UPhysicsCollisionHandler;
	class UTexture;
	class UTexture2D;
	class UTexture2DArray;
	class UTimecodeProvider;
	class UVolumeTexture;
	class UWorld;

	using FBrowseURL = TDelegate<EBrowseReturnVal::Type(FWorldContext&, FURL, FString&)>;
	using FEngineHitchDetectedDelegate = TMulticastDelegate<void(EFrameHitchType, float)>;
	using FPendingLevelUpdate = TDelegate<void(FWorldContext&, float)>;

	class UEngine :
		public UObject,
		public FExec
	{
	public:
		UE_DEFINE_UOBJECT(UEngine, UObject, "Engine", "Engine");

		using FEngineStatRender = TDelegate<std::int32_t(UWorld*, FViewport*, FCanvas*, std::int32_t, std::int32_t, const FVector*, const FRotator*)>;
		using FEngineStatToggle = TDelegate<bool(UWorld*, FCommonViewportClient*, const wchar_t*)>;
		using FOnNetworkDDoSEscalation = TMulticastDelegate<void(UWorld*, UNetDriver*, FString)>;
		using FOnNetworkFailure = TMulticastDelegate<void(UWorld*, UNetDriver*, ENetworkFailure::Type, const FString&)>;
		using FOnNetworkLagStateChanged = TMulticastDelegate<void(UWorld*, UNetDriver*, ENetworkLagState::Type)>;
		using FOnTravelFailure = TMulticastDelegate<void(UWorld*, ETravelFailure::Type, const FString&)>;
		using FWorldAddedEvent = TMulticastDelegate<void(UWorld*)>;
		using FWorldDestroyedEvent = TMulticastDelegate<void(UWorld*)>;

		class FEngineStatFuncs
		{
		public:
			FName             commandName;        // 00
			FString           commandNameString;  // 08
			FName             categoryName;       // 18
			FText             descriptionString;  // 20
			FEngineStatRender renderFunc;         // 38
			FEngineStatToggle toggleFunc;         // 48
			bool              isRHS;              // 58
		};
		static_assert(sizeof(FEngineStatFuncs) == 0x60);

		// override
		virtual ~UEngine();  // 00

		// add
		virtual void                   WorldAdded(UWorld*);                                                                   // 57
		virtual void                   WorldDestroyed(UWorld*);                                                               // 58
		virtual bool                   IsInitialized();                                                                       // 59
		virtual ERHIFeatureLevel::Type GetDefaultWorldFeatureLevel();                                                         // 5A
		virtual void                   Init(IEngineLoop*);                                                                    // 5B
		virtual void                   Start();                                                                               // 5C
		virtual void                   PreExit();                                                                             // 5D
		virtual void                   ReleaseAudioDeviceManager();                                                           // 5E
		virtual void                   Tick(float, bool);                                                                     // 5F
		virtual void                   UpdateTimeAndHandleMaxTickRate();                                                      // 60
		virtual long double            CorrectNegativeTimeDelta(long double);                                                 // 61
		virtual float                  GetMaxTickRate(float, bool);                                                           // 62
		virtual float                  GetMaxFPS();                                                                           // 63
		virtual void                   SetMaxFPS(const float);                                                                // 64
		virtual void                   UpdateRunningAverageDeltaTime(float, bool);                                            // 65
		virtual bool                   IsAllowedFramerateSmoothing();                                                         // 66
		virtual bool                   IsRenderingSuspended();                                                                // 67
		virtual void                   OnLostFocusPause(bool);                                                                // 68
		virtual bool                   ShouldThrottleCPUUsage();                                                              // 69
		virtual bool                   IsControllerIdUsingPlatformUserId();                                                   // 6A
		virtual bool                   ShouldDrawBrushWireframe(AActor*);                                                     // 6B
		virtual bool                   GetMapBuildCancelled();                                                                // 6C
		virtual void                   SetMapBuildCancelled(bool);                                                            // 6D
		virtual bool                   IsPropertyColorationColorFeatureActivated();                                           // 6E
		virtual bool                   GetPropertyColorationColor(UObject*, FColor*);                                         // 6F
		virtual bool                   AllowSelectTranslucent();                                                              // 70
		virtual bool                   OnlyLoadEditorVisibleLevelsInPIE();                                                    // 71
		virtual bool                   PreferToStreamLevelsInPIE();                                                           // 72
		virtual int                    GetSpriteCategoryIndex(const FName*);                                                  // 73
		virtual float                  GetTimeBetweenGarbageCollectionPasses(bool);                                           // 74
		virtual void                   StartFPSChart(const FString*, bool);                                                   // 75
		virtual void                   StopFPSChart(const FString*);                                                          // 76
		virtual void                   ProcessToggleFreezeCommand(UWorld*);                                                   // 77
		virtual void                   ProcessToggleFreezeStreamingCommand(UWorld*);                                          // 78
		virtual EGarbageCollectionType ShouldForceGarbageCollection();                                                        // 79
		virtual bool                   IsSplitScreen(UWorld*);                                                                // 7A
		virtual bool                   HasMultipleLocalPlayers(UWorld*);                                                      // 7B
		virtual bool                   IsSettingUpPlayWorld();                                                                // 7C
		virtual TSharedPtr<SViewport>* GetGameViewportWidget(TSharedPtr<SViewport>* result);                                  // 7D
		virtual void                   FocusNextPIEWorld(UWorld*, bool);                                                      // 7E
		virtual void                   ResetPIEAudioSetting(UWorld*);                                                         // 7F
		virtual UGameViewportClient*   GetNextPIEViewport(UGameViewportClient*);                                              // 80
		virtual void                   RemapGamepadControllerIdForPIE(UGameViewportClient*, int*);                            // 81
		virtual void                   NotifyToolsOfObjectReplacement(const TMap<UObject*, UObject*>*);                       // 82
		virtual bool                   UseSound();                                                                            // 83
		virtual UWorld*                CreatePIEWorldByDuplication(FWorldContext*, UWorld*, FString*);                        // 84
		virtual void                   PostCreatePIEWorld(UWorld*);                                                           // 85
		virtual bool                   Experimental_ShouldPreDuplicateMap(const FName);                                       // 86
		virtual void                   InitializeAudioDeviceManager();                                                        // 87
		virtual bool                   InitializeHMDDevice();                                                                 // 88
		virtual bool                   InitializeEyeTrackingDevice();                                                         // 89
		virtual void                   RecordHMDAnalytics();                                                                  // 8A
		virtual void                   InitializeObjectReferences();                                                          // 8B
		virtual void                   InitializePortalServices();                                                            // 8C
		virtual void                   InitializeRunningAverageDeltaTime();                                                   // 8D
		virtual void                   SpawnServerActors(UWorld*);                                                            // 8E
		virtual void                   HandleNetworkFailure(UWorld*, UNetDriver*, ENetworkFailure::Type, const FString*);     // 8F
		virtual void                   HandleTravelFailure(UWorld*, ETravelFailure::Type, const FString*);                    // 90
		virtual void                   HandleNetworkLagStateChanged(UWorld*, UNetDriver*, ENetworkLagState::Type);            // 91
		virtual bool                   NetworkRemapPath(UPendingNetGame*, FString*, bool);                                    // 92
		virtual bool                   NetworkRemapPath(UNetConnection*, FString*, bool);                                     // 93
		virtual bool                   HandleOpenCommand(const wchar_t*, FOutputDevice*, UWorld*);                            // 94
		virtual bool                   HandleTravelCommand(const wchar_t*, FOutputDevice*, UWorld*);                          // 95
		virtual bool                   HandleStreamMapCommand(const wchar_t*, FOutputDevice*, UWorld*);                       // 96
		virtual bool                   HandleServerTravelCommand(const wchar_t*, FOutputDevice*, UWorld*);                    // 97
		virtual bool                   HandleDisconnectCommand(const wchar_t*, FOutputDevice*, UWorld*);                      // 98
		virtual bool                   HandleReconnectCommand(const wchar_t*, FOutputDevice*, UWorld*);                       // 99
		virtual EBrowseReturnVal::Type Browse(FWorldContext*, FURL, FString*);                                                // 9A
		virtual void                   TickWorldTravel(FWorldContext*, float);                                                // 9B
		virtual bool                   LoadMap(FWorldContext*, FURL, UPendingNetGame*, FString*);                             // 9C
		virtual void                   RedrawViewports(bool);                                                                 // 9D
		virtual void                   TriggerStreamingDataRebuild();                                                         // 9E
		virtual void                   LoadMapRedrawViewports();                                                              // 9F
		virtual void                   CancelAllPending();                                                                    // A0
		virtual void                   CancelPending(UNetDriver*);                                                            // A1
		virtual void                   CancelPending(FWorldContext*);                                                         // A2
		virtual void                   CancelPending(UWorld*, UPendingNetGame*);                                              // A3
		virtual bool                   WorldIsPIEInNewViewport(UWorld*);                                                      // A4
		virtual void                   CheckAndHandleStaleWorldObjectReferences(FWorldContext*);                              // A5
		virtual void                   DestroyWorldContext(UWorld*);                                                          // A6
		virtual bool                   AreEditorAnalyticsEnabled();                                                           // A7
		virtual void                   CreateStartupAnalyticsAttributes(TArray<FAnalyticsEventAttribute>*);                   // A8
		virtual bool                   IsAutosaving();                                                                        // A9
		virtual bool                   ShouldDoAsyncEndOfFrameTasks();                                                        // AA
		virtual void                   MovePendingLevel(FWorldContext*);                                                      // AB
		virtual bool                   ShouldShutdownWorldNetDriver();                                                        // AC
		virtual void                   HandleBrowseToDefaultMapFailure(FWorldContext*, const FString*, const FString*);       // AD
		virtual void                   HandleNetworkFailure_NotifyGameInstance(UWorld*, UNetDriver*, ENetworkFailure::Type);  // AE
		virtual void                   HandleTravelFailure_NotifyGameInstance(UWorld*, ETravelFailure::Type);                 // AF

		static UEngine* GetSingleton()
		{
			using func_t = decltype(&UEngine::GetSingleton);
			static REL::Relocation<UEngine**> singleton{ ID::UEngine::GetSingleton };
			return *singleton;
		}

		UWorld* GetCurrentPlayWorld(UWorld* a_possiblePlayWorld)
		{
			using func_t = decltype(&UEngine::GetCurrentPlayWorld);
			static REL::Relocation<func_t> func{ ID::UEngine::GetCurrentPlayWorld };
			return func(this, a_possiblePlayWorld);
		}

		// members
		TObjectPtr<UFont>                            tinyFont;                                            // 030
		FSoftObjectPath                              tinyFontName;                                        // 038
		TObjectPtr<UFont>                            smallFont;                                           // 058
		FSoftObjectPath                              smallFontName;                                       // 060
		TObjectPtr<UFont>                            mediumFont;                                          // 080
		FSoftObjectPath                              mediumFontName;                                      // 088
		TObjectPtr<UFont>                            largeFont;                                           // 0A8
		FSoftObjectPath                              largeFontName;                                       // 0B0
		TObjectPtr<UFont>                            subtitleFont;                                        // 0D0
		FSoftObjectPath                              subtitleFontName;                                    // 0D8
		TArray<TObjectPtr<UFont>>                    additionalFonts;                                     //
		TArray<FString>                              additionalFontNames;                                 //
		TSubclassOf<UConsole>                        consoleClass;                                        //
		FSoftClassPath                               consoleClassName;                                    //
		TSubclassOf<UGameViewportClient>             gameViewportClientClass;                             //
		FSoftClassPath                               gameViewportClientClassName;                         //
		TSubclassOf<ULocalPlayer>                    localPlayerClass;                                    //
		FSoftClassPath                               localPlayerClassName;                                //
		TSubclassOf<AWorldSettings>                  worldSettingsClass;                                  //
		FSoftClassPath                               worldSettingsClassName;                              //
		FSoftClassPath                               navigationSystemClassName;                           //
		TSubclassOf<UNavigationSystemBase>           navigationSystemClass;                               //
		FSoftClassPath                               navigationSystemConfigClassName;                     //
		TSubclassOf<UNavigationSystemConfig>         navigationSystemConfigClass;                         //
		FSoftClassPath                               avoidanceManagerClassName;                           //
		TSubclassOf<UAvoidanceManager>               avoidanceManagerClass;                               //
		FSoftClassPath                               aiControllerClassName;                               //
		TSubclassOf<UPhysicsCollisionHandler>        physicsCollisionHandlerClass;                        //
		FSoftClassPath                               physicsCollisionHandlerClassName;                    //
		FSoftClassPath                               gameUserSettingsClassName;                           //
		TSubclassOf<UGameUserSettings>               gameUserSettingsClass;                               //
		TObjectPtr<UGameUserSettings>                gameUserSettings;                                    //
		TSubclassOf<ALevelScriptActor>               levelScriptActorClass;                               //
		FSoftClassPath                               levelScriptActorClassName;                           //
		FSoftClassPath                               defaultBlueprintBaseClassName;                       //
		FSoftClassPath                               gameSingletonClassName;                              //
		TObjectPtr<UObject>                          gameSingleton;                                       //
		FSoftClassPath                               assetManagerClassName;                               //
		TObjectPtr<UAssetManager>                    assetManager;                                        //
		TObjectPtr<UTexture2D>                       defaultTexture;                                      //
		FSoftObjectPath                              defaultTextureName;                                  //
		TObjectPtr<UTexture>                         defaultDiffuseTexture;                               //
		FSoftObjectPath                              defaultDiffuseTextureName;                           //
		TObjectPtr<UTexture2D>                       defaultBSPVertexTexture;                             //
		FSoftObjectPath                              defaultBSPVertexTextureName;                         //
		TObjectPtr<UTexture2D>                       highFrequencyNoiseTexture;                           //
		FSoftObjectPath                              highFrequencyNoiseTextureName;                       //
		TObjectPtr<UTexture2D>                       defaultBokehTexture;                                 //
		FSoftObjectPath                              defaultBokehTextureName;                             //
		TObjectPtr<UTexture2D>                       defaultBloomKernelTexture;                           //
		FSoftObjectPath                              defaultBloomKernelTextureName;                       //
		TObjectPtr<UTexture2D>                       defaultFilmGrainTexture;                             //
		FSoftObjectPath                              defaultFilmGrainTextureName;                         //
		TObjectPtr<UMaterial>                        wireframeMaterial;                                   //
		FString                                      wireframeMaterialName;                               //
		TObjectPtr<UMaterial>                        debugMeshMaterial;                                   //
		FSoftObjectPath                              debugMeshMaterialName;                               //
		TObjectPtr<UMaterial>                        naniteHiddenSectionMaterial;                         //
		FString                                      naniteHiddenSectionMaterialName;                     //
		TObjectPtr<UMaterial>                        emissiveMeshMaterial;                                //
		FSoftObjectPath                              emissiveMeshMaterialName;                            //
		TObjectPtr<UMaterial>                        levelColorationLitMaterial;                          //
		FString                                      levelColorationLitMaterialName;                      //
		TObjectPtr<UMaterial>                        levelColorationUnlitMaterial;                        //
		FString                                      levelColorationUnlitMaterialName;                    //
		TObjectPtr<UMaterial>                        lightingTexelDensityMaterial;                        //
		FString                                      lightingTexelDensityName;                            //
		TObjectPtr<UMaterial>                        shadedLevelColorationLitMaterial;                    //
		FString                                      shadedLevelColorationLitMaterialName;                //
		TObjectPtr<UMaterial>                        shadedLevelColorationUnlitMaterial;                  //
		FString                                      shadedLevelColorationUnlitMaterialName;              //
		TObjectPtr<UMaterial>                        removeSurfaceMaterial;                               //
		FSoftObjectPath                              removeSurfaceMaterialName;                           //
		TObjectPtr<UMaterial>                        vertexColorMaterial;                                 //
		FString                                      vertexColorMaterialName;                             //
		TObjectPtr<UMaterial>                        vertexColorViewModeMaterial_ColorOnly;               //
		FString                                      vertexColorViewModeMaterialName_ColorOnly;           //
		TObjectPtr<UMaterial>                        vertexColorViewModeMaterial_AlphaAsColor;            //
		FString                                      vertexColorViewModeMaterialName_AlphaAsColor;        //
		TObjectPtr<UMaterial>                        vertexColorViewModeMaterial_RedOnly;                 //
		FString                                      vertexColorViewModeMaterialName_RedOnly;             //
		TObjectPtr<UMaterial>                        vertexColorViewModeMaterial_GreenOnly;               //
		FString                                      vertexColorViewModeMaterialName_GreenOnly;           //
		TObjectPtr<UMaterial>                        vertexColorViewModeMaterial_BlueOnly;                //
		FString                                      vertexColorViewModeMaterialName_BlueOnly;            //
		FSoftObjectPath                              debugEditorMaterialName;                             //
		TObjectPtr<UMaterial>                        constraintLimitMaterial;                             //
		TObjectPtr<UMaterialInstanceDynamic>         constraintLimitMaterialX;                            //
		TObjectPtr<UMaterialInstanceDynamic>         constraintLimitMaterialXAxis;                        //
		TObjectPtr<UMaterialInstanceDynamic>         constraintLimitMaterialY;                            //
		TObjectPtr<UMaterialInstanceDynamic>         constraintLimitMaterialYAxis;                        //
		TObjectPtr<UMaterialInstanceDynamic>         constraintLimitMaterialZ;                            //
		TObjectPtr<UMaterialInstanceDynamic>         constraintLimitMaterialZAxis;                        //
		TObjectPtr<UMaterialInstanceDynamic>         constraintLimitMaterialPrismatic;                    //
		TObjectPtr<UMaterial>                        invalidLightmapSettingsMaterial;                     //
		FSoftObjectPath                              invalidLightmapSettingsMaterialName;                 //
		TObjectPtr<UMaterial>                        previewShadowsIndicatorMaterial;                     //
		FSoftObjectPath                              previewShadowsIndicatorMaterialName;                 //
		TObjectPtr<UMaterial>                        arrowMaterial;                                       //
		TObjectPtr<UMaterialInstanceDynamic>         arrowMaterialYellow;                                 //
		FSoftObjectPath                              arrowMaterialName;                                   //
		FLinearColor                                 lightingOnlyBrightness;                              //
		TArray<FLinearColor>                         shaderComplexityColors;                              //
		TArray<FLinearColor>                         quadComplexityColors;                                //
		TArray<FLinearColor>                         lightComplexityColors;                               //
		TArray<FLinearColor>                         stationaryLightOverlapColors;                        //
		TArray<FLinearColor>                         lodColorationColors;                                 //
		TArray<FLinearColor>                         hlodColorationColors;                                //
		TArray<FLinearColor>                         streamingAccuracyColors;                             //
		FLinearColor                                 gpuSkinCacheVisualizationExcludedColor;              //
		FLinearColor                                 gpuSkinCacheVisualizationIncludedColor;              //
		FLinearColor                                 gpuSkinCacheVisualizationRecomputeTangentsColor;     //
		float                                        gpuSkinCacheVisualizationLowMemoryThresholdInMB;     //
		float                                        gpuSkinCacheVisualizationHighMemoryThresholdInMB;    //
		FLinearColor                                 gpuSkinCacheVisualizationLowMemoryColor;             //
		FLinearColor                                 gpuSkinCacheVisualizationMidMemoryColor;             //
		FLinearColor                                 gpuSkinCacheVisualizationHighMemoryColor;            //
		TArray<FLinearColor>                         gpuSkinCacheVisualizationRayTracingLODOffsetColors;  //
		float                                        maxPixelShaderAdditiveComplexityCount;               //
		float                                        maxES3PixelShaderAdditiveComplexityCount;            //
		float                                        minLightMapDensity;                                  //
		float                                        idealLightMapDensity;                                //
		float                                        maxLightMapDensity;                                  //
		std::uint32_t                                renderLightMapDensityGrayscale: 1;                   //
		float                                        renderLightMapDensityGrayscaleScale;                 //
		float                                        renderLightMapDensityColorScale;                     //
		FLinearColor                                 lightMapDensityVertexMappedColor;                    //
		FLinearColor                                 lightMapDensitySelectedColor;                        //
		TArray<FStatColorMapping>                    statColorMappings;                                   //
		TObjectPtr<UPhysicalMaterial>                defaultPhysMaterial;                                 //
		FSoftObjectPath                              defaultPhysMaterialName;                             //
		TObjectPtr<UPhysicalMaterial>                defaultDestructiblePhysMaterial;                     //
		FSoftObjectPath                              defaultDestructiblePhysMaterialName;                 //
		TArray<FGameNameRedirect>                    activeGameNameRedirects;                             //
		TArray<FClassRedirect>                       activeClassRedirects;                                //
		TArray<FPluginRedirect>                      activePluginRedirects;                               //
		TArray<FStructRedirect>                      activeStructRedirects;                               //
		TObjectPtr<UTexture2D>                       preIntegratedSkinBRDFTexture;                        //
		FSoftObjectPath                              preIntegratedSkinBRDFTextureName;                    //
		TObjectPtr<UTexture2D>                       blueNoiseScalarTexture;                              //
		TObjectPtr<UTexture2D>                       blueNoiseVec2Texture;                                //
		FSoftObjectPath                              blueNoiseScalarTextureName;                          //
		FSoftObjectPath                              blueNoiseVec2TextureName;                            //
		TObjectPtr<UTexture2DArray>                  glintTexture;                                        //
		TObjectPtr<UTexture2DArray>                  glintTexture2;                                       //
		FSoftObjectPath                              glintTextureName;                                    //
		FSoftObjectPath                              glintTexture2Name;                                   //
		TObjectPtr<UVolumeTexture>                   simpleVolumeTexture;                                 //
		FSoftObjectPath                              simpleVolumeTextureName;                             //
		TObjectPtr<UVolumeTexture>                   simpleVolumeEnvTexture;                              //
		FSoftObjectPath                              simpleVolumeEnvTextureName;                          //
		TObjectPtr<UTexture2D>                       miniFontTexture;                                     //
		FSoftObjectPath                              miniFontTextureName;                                 //
		TObjectPtr<UTexture>                         weightMapPlaceholderTexture;                         //
		FSoftObjectPath                              weightMapPlaceholderTextureName;                     //
		TObjectPtr<UTexture2D>                       lightMapDensityTexture;                              //
		FSoftObjectPath                              lightMapDensityTextureName;                          //
		IEngineLoop*                                 engineLoop;                                          //
		TObjectPtr<UGameViewportClient>              gameViewport;                                        //
		TArray<FString>                              deferredCommands;                                    //
		float                                        nearClipPlane;                                       //
		std::uint32_t                                subtitlesEnabled: 1;                                 //
		std::uint32_t                                subtitlesForcedOff: 1;                               //
		std::int32_t                                 maximumLoopIterationCount;                           //
		std::uint32_t                                canBlueprintsTickByDefault: 1;                       //
		std::uint32_t                                optimizeAnimBlueprintMemberVariableAccess: 1;        //
		std::uint32_t                                allowMultiThreadedAnimationUpdate: 1;                //
		std::uint32_t                                enableEditorPSysRealtimeLOD: 1;                      //
		std::uint32_t                                forceDisableFrameRateSmoothing: 1;                   //
		std::uint32_t                                smoothFrameRate: 1;                                  //
		std::uint32_t                                useFixedFrameRate: 1;                                //
		float                                        fixedFrameRate;                                      //
		std::byte                                    smoothedFrameRateRange[0x10];                        // - FFloatRange
		TObjectPtr<UEngineCustomTimeStep>            customTimeStep;                                      //
		TMulticastDelegate<void(void)>               customTimeStepChangedEvent;                          //
		bool                                         isCurrentCustomTimeStepInitialized;                  //
		FSoftClassPath                               customTimeStepClassName;                             //
		TObjectPtr<UTimecodeProvider>                timecodeProvider;                                    //
		TMulticastDelegate<void(void)>               timecodeProviderChangedEvent;                        //
		bool                                         isCurrentTimecodeProviderInitialized;                //
		FSoftClassPath                               timecodeProviderClassName;                           //
		bool                                         generateDefaultTimecode;                             //
		FFrameRate                                   generateDefaultTimecodeFrameRate;                    //
		float                                        generateDefaultTimecodeFrameDelay;                   //
		std::uint32_t                                checkForMultiplePawnsSpawnedInAFrame: 1;             //
		int                                          numPawnsAllowedToBeSpawnedInAFrame;                  //
		std::uint32_t                                shouldGenerateLowQualityLightmaps_DEPRECATED: 1;     //
		FColor                                       colorWorldBox;                                       //
		FColor                                       colorBrushWire;                                      //
		FColor                                       colorAddWire;                                        //
		FColor                                       colorSubtractWire;                                   //
		FColor                                       colorSemiSolidWire;                                  //
		FColor                                       colorNonSolidWire;                                   //
		FColor                                       colorWireBackground;                                 //
		FColor                                       colorScaleBoxHi;                                     //
		FColor                                       colorVolumeCollision;                                //
		FColor                                       colorBSPCollision;                                   //
		FColor                                       colorOrthoBackground;                                //
		FColor                                       colorVolume;                                         //
		FColor                                       colorBrushShape;                                     //
		float                                        streamingDistanceFactor;                             //
		FDirectoryPath                               gameScreenshotSaveDirectory;                         //
		bool                                         useStaticMeshMinLODPerQualityLevels;                 //
		bool                                         useSkeletalMeshMinLODPerQualityLevels;               //
		bool                                         useGrassVarityPerQualityLevels;                      //
		ETransitionType                              transitionType;                                      //
		FString                                      transitionDescription;                               //
		FString                                      transitionGameMode;                                  //
		std::uint32_t                                allowMatureLanguage: 1;                              //
		float                                        cameraRotationThreshold;                             //
		float                                        cameraTranslationThreshold;                          //
		float                                        primitiveProbablyVisibleTime;                        //
		float                                        maxOcclusionPixelsFraction;                          //
		std::uint32_t                                pauseOnLossOfFocus: 1;                               //
		int                                          maxParticleResize;                                   //
		int                                          maxParticleResizeWarn;                               //
		TArray<FDropNoteInfo>                        pendingDroppedNotes;                                 //
		float                                        netClientTicksPerSecond;                             //
		float                                        displayGamma;                                        //
		float                                        minDesiredFrameRate;                                 //
		FLinearColor                                 defaultSelectedMaterialColor;                        //
		FLinearColor                                 selectedMaterialColor;                               //
		FLinearColor                                 selectionOutlineColor;                               //
		FLinearColor                                 subduedSelectionOutlineColor;                        //
		FLinearColor                                 selectedMaterialColorOverride;                       //
		bool                                         isOverridingSelectedColor;                           //
		std::uint32_t                                enableOnScreenDebugMessages: 1;                      //
		std::uint32_t                                enableOnScreenDebugMessagesDisplay: 1;               //
		std::uint32_t                                suppressMapWarnings: 1;                              //
		std::uint32_t                                disableAILogging: 1;                                 //
		std::uint32_t                                enableVisualLogRecordingOnStart;                     //
		std::int32_t                                 screenSaverInhibitorSemaphore;                       //
		std::uint32_t                                lockReadOnlyLevels: 1;                               //
		FString                                      particleEventManagerClassPath;                       //
		float                                        selectionHighlightIntensity;                         //
		float                                        bspSelectionHighlightIntensity;                      //
		float                                        selectionHighlightIntensityBillboards;               //
		TDelegate<void(FViewport*)>*                 beginStreamingPauseDelegate;                         //
		TDelegate<void()>*                           endStreamingPauseDelegate;                           //
		TMulticastDelegate<void()>                   preRenderDelegate;                                   //
		TMulticastDelegate<void(FRDGBuilder&)>       preRenderDelegateEx;                                 //
		TMulticastDelegate<void()>                   postRenderDelegate;                                  //
		TMulticastDelegate<void(FRDGBuilder&)>       postRenderDelegateEx;                                //
		FOnTravelFailure                             travelFailureEvent;                                  //
		FOnNetworkFailure                            networkFailureEvent;                                 //
		FOnNetworkLagStateChanged                    networkLagStateChangedEvent;                         //
		FOnNetworkDDoSEscalation                     networkDDoSEscalationEvent;                          //
		bool                                         isInitialized;                                       //
		std::uint64_t                                lastGCFrame;                                         //
		float                                        timeSinceLastPendingKillPurge;                       //
		bool                                         fullPurgeTriggered;                                  //
		bool                                         shouldDelayGarbageCollect;                           //
		EDynamicResolutionStateEvent                 lastDynamicResolutionEvent;                          //
		TSharedPtr<IDynamicResolutionState>          dynamicResolutionState;                              //
		TSharedPtr<IDynamicResolutionState>          nextDynamicResolutionState;                          //
		bool                                         isDynamicResolutionPaused;                           //
		bool                                         dynamicResolutionEnableUserSetting;                  //
		FAudioDeviceManager*                         audioDeviceManager;                                  //
		FAudioDeviceHandle                           mainAudioDeviceHandle;                               //
		TArray<FScreenMessageString>                 priorityScreenMessages;                              //
		TMap<std::int32_t, FScreenMessageString>     screenMessages;                                      //
		TSharedPtr<IStereoRendering>                 stereoRenderingDevice;                               //
		TSharedPtr<IXRTrackingSystem>                xrSystem;                                            //
		TSharedPtr<FSceneViewExtensions>             viewExtensions;                                      //
		TSharedPtr<IEyeTracker>                      eyeTrackingDevice;                                   //
		FEngineHitchDetectedDelegate                 onHitchDetectedDelegate;                             //
		TSharedPtr<IMessageRpcClient>                portalRpcClient;                                     //
		TSharedPtr<IPortalRpcLocator>                portalRpcLocator;                                    //
		TSharedPtr<FTypeContainer>                   serviceDependencies;                                 //
		TSharedPtr<IPortalServiceLocator>            serviceLocator;                                      //
		TSharedPtr<FPerformanceTrackingChart>        activePerformanceChart;                              //
		TArray<TSharedPtr<IPerformanceDataConsumer>> activePerformanceDataConsumers;                      //
		float                                        runningAverageDeltaTime;                             //
		FWorldAddedEvent                             worldAddedEvent;                                     //
		FWorldDestroyedEvent                         worldDestroyedEvent;                                 //
		FRunnableThread*                             screenSaverInhibitor;                                //
		FScreenSaverInhibitor*                       screenSaverInhibitorRunnable;                        //
		std::uint32_t                                globalNetTravelCount;                                //
		TArray<FNetDriverDefinition>                 netDriverDefinitions;                                //
		TArray<FIrisNetDriverConfig>                 irisNetDriverConfigs;                                //
		TArray<FString>                              serverActors;                                        //
		TArray<FString>                              runtimeServerActors;                                 //
		float                                        netErrorLogInterval;                                 //
		std::uint32_t                                startedLoadMapMovie: 1;                              //
		bool                                         isVanillaProduct;                                    //
		FBrowseURL                                   onOverrideBrowseURL;                                 //
		FPendingLevelUpdate                          onOverridePendingNetGameUpdate;                      //
		TIndirectArray<FWorldContext>                worldList;                                           //
		std::int32_t                                 nextWorldContextHandle;                              //
		FObjectSubsystemCollection<UEngineSubsystem> engineSubsystemCollection;                           //
		TArray<FEngineStatFuncs>                     engineStats;                                         //
		std::uintptr_t                               errorsAndWarningsCollector;                          // - TPimplPtr<FErrorsAndWarningsCollector>
		FDelegateHandle                              handleScreenshotCapturedDelegateHandle;              //
	};
	static_assert(sizeof(UEngine) == 0x1078);
}
