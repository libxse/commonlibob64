#pragma once

#include "UE/E/ECanBeCharacterBase.h"
#include "UE/E/EComponentPhysicsStateChange.h"
#include "UE/E/EDOFMode.h"
#include "UE/E/EDecalChannels.h"
#include "UE/E/EHLODBatchingPolicy.h"
#include "UE/E/EHasCustomNavigableGeometry.h"
#include "UE/E/EIndirectLightingCacheQuality.h"
#include "UE/E/ELightMapInteractionType.h"
#include "UE/E/ELightmapType.h"
#include "UE/E/EMaterialQualityLevel.h"
#include "UE/E/ERHIFeatureLevel.h"
#include "UE/E/ERadialImpulseFalloff.h"
#include "UE/E/ERayTracingGroupCullingPriority.h"
#include "UE/E/ERendererStencilMask.h"
#include "UE/E/ERuntimeVirtualTextureMainPassType.h"
#include "UE/E/ESceneDepthPriorityGroup.h"
#include "UE/E/EShadowCacheInvalidationBehavior.h"
#include "UE/E/ETextureStreamingBuildType.h"
#include "UE/E/ETouchIndex.h"
#include "UE/F/FCustomPrimitiveData.h"
#include "UE/F/FKey.h"
#include "UE/F/FLightingChannels.h"
#include "UE/F/FMatrix.h"
#include "UE/F/FPrimitiveComponentId.h"
#include "UE/F/FRenderCommandFence.h"
#include "UE/I/IInterface_AsyncCompilation.h"
#include "UE/I/INavRelevantInterface.h"
#include "UE/I/IPhysicsComponent.h"
#include "UE/U/USceneComponent.h"

namespace UE::Chaos
{
	class FImplicitObject;
}

namespace UE
{
	class APawn;
	class AController;
	class FBodyInstance;
	class FCollisionObjectQueryParams;
	class FCollisionQueryParams;
	class FCollisionResponseParams;
	class FCollisionShape;
	class FComponentBeginCursorOverSignatureInfoGetter;
	class FComponentBeginOverlapSignatureInfoGetter;
	class FComponentBeginTouchOverSignatureInfoGetter;
	class FComponentCollisionSettingsChangedSignatureInfoGetter;
	class FComponentEndCursorOverSignatureInfoGetter;
	class FComponentEndOverlapSignatureInfoGetter;
	class FComponentEndTouchOverSignatureInfoGetter;
	class FComponentHitSignatureInfoGetter;
	class FComponentOnClickedSignatureInfoGetter;
	class FComponentOnInputTouchBeginSignatureInfoGetter;
	class FComponentOnInputTouchEndSignatureInfoGetter;
	class FComponentOnReleasedSignatureInfoGetter;
	class FComponentPhysicsStateChangedInfoGetter;
	class FComponentQueryParams;
	class FComponentSleepSignatureInfoGetter;
	class FComponentWakeSignatureInfoGetter;
	class FDamageEvent;
	class FEngineShowFlags;
	class FMTDResult;
	class FOverlapResult;
	class FPhysScene_Chaos;
	class FPrimitiveSceneProxy;
	class FPSOPrecacheParams;
	class FPSOPrecacheVertexFactoryData;
	class FStreamingRenderAssetPrimitiveInfo;
	class FStreamingTextureLevelContext;
	class FWalkableSlopeOverride;
	class UBodySetup;
	class UMaterialInstanceDynamic;
	class UMaterialInterface;
	class UPhysicalMaterial;
	class UPrimitiveComponent;
	class URuntimeVirtualTexture;
	class UTexture;

	using FComponentBeginCursorOverSignature_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, UPrimitiveComponent*>;
	using FComponentBeginCursorOverSignature = TSparseDynamicDelegate<FComponentBeginCursorOverSignature_MCSignature, UPrimitiveComponent, FComponentBeginCursorOverSignatureInfoGetter>;
	using FComponentBeginOverlapSignature_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, UPrimitiveComponent*, AActor*, UPrimitiveComponent*, std::int32_t, bool, const FHitResult&>;
	using FComponentBeginOverlapSignature = TSparseDynamicDelegate<FComponentBeginOverlapSignature_MCSignature, UPrimitiveComponent, FComponentBeginOverlapSignatureInfoGetter>;
	using FComponentBeginTouchOverSignature_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, ETouchIndex, UPrimitiveComponent*>;
	using FComponentBeginTouchOverSignature = TSparseDynamicDelegate<FComponentBeginTouchOverSignature_MCSignature, UPrimitiveComponent, FComponentBeginTouchOverSignatureInfoGetter>;
	using FComponentCollisionSettingsChangedSignature_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, UPrimitiveComponent*>;
	using FComponentCollisionSettingsChangedSignature = TSparseDynamicDelegate<FComponentCollisionSettingsChangedSignature_MCSignature, UPrimitiveComponent, FComponentCollisionSettingsChangedSignatureInfoGetter>;
	using FComponentEndCursorOverSignature_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, UPrimitiveComponent*>;
	using FComponentEndCursorOverSignature = TSparseDynamicDelegate<FComponentEndCursorOverSignature_MCSignature, UPrimitiveComponent, FComponentEndCursorOverSignatureInfoGetter>;
	using FComponentEndOverlapSignature_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, UPrimitiveComponent*, AActor*, UPrimitiveComponent*, std::int32_t>;
	using FComponentEndOverlapSignature = TSparseDynamicDelegate<FComponentEndOverlapSignature_MCSignature, UPrimitiveComponent, FComponentEndOverlapSignatureInfoGetter>;
	using FComponentEndTouchOverSignature_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, ETouchIndex, UPrimitiveComponent*>;
	using FComponentEndTouchOverSignature = TSparseDynamicDelegate<FComponentEndTouchOverSignature_MCSignature, UPrimitiveComponent, FComponentEndTouchOverSignatureInfoGetter>;
	using FComponentHitSignature_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, UPrimitiveComponent*, AActor*, UPrimitiveComponent*, FVector, const FHitResult&>;
	using FComponentHitSignature = TSparseDynamicDelegate<FComponentHitSignature_MCSignature, UPrimitiveComponent, FComponentHitSignatureInfoGetter>;
	using FComponentOnClickedSignature_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, UPrimitiveComponent*, FKey>;
	using FComponentOnClickedSignature = TSparseDynamicDelegate<FComponentOnClickedSignature_MCSignature, UPrimitiveComponent, FComponentOnClickedSignatureInfoGetter>;
	using FComponentOnInputTouchBeginSignature_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, ETouchIndex, UPrimitiveComponent*>;
	using FComponentOnInputTouchBeginSignature = TSparseDynamicDelegate<FComponentOnInputTouchBeginSignature_MCSignature, UPrimitiveComponent, FComponentOnInputTouchBeginSignatureInfoGetter>;
	using FComponentOnInputTouchEndSignature_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, ETouchIndex, UPrimitiveComponent*>;
	using FComponentOnInputTouchEndSignature = TSparseDynamicDelegate<FComponentOnInputTouchEndSignature_MCSignature, UPrimitiveComponent, FComponentOnInputTouchEndSignatureInfoGetter>;
	using FComponentOnReleasedSignature_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, UPrimitiveComponent*, FKey>;
	using FComponentOnReleasedSignature = TSparseDynamicDelegate<FComponentOnReleasedSignature_MCSignature, UPrimitiveComponent, FComponentOnReleasedSignatureInfoGetter>;
	using FComponentPhysicsStateChanged_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, UPrimitiveComponent*, EComponentPhysicsStateChange>;
	using FComponentPhysicsStateChanged = TSparseDynamicDelegate<FComponentPhysicsStateChanged_MCSignature, UPrimitiveComponent, FComponentPhysicsStateChangedInfoGetter>;
	using FComponentSleepSignature_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, UPrimitiveComponent*, FName>;
	using FComponentSleepSignature = TSparseDynamicDelegate<FComponentSleepSignature_MCSignature, UPrimitiveComponent, FComponentSleepSignatureInfoGetter>;
	using FComponentWakeSignature_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, UPrimitiveComponent*, FName>;
	using FComponentWakeSignature = TSparseDynamicDelegate<FComponentWakeSignature_MCSignature, UPrimitiveComponent, FComponentWakeSignatureInfoGetter>;
	using FPhysicsGeometry = Chaos::FImplicitObject;
	using FPSOPrecacheVertexFactoryDataList = TArray<FPSOPrecacheVertexFactoryData, TInlineAllocator<2>>;

	class UPrimitiveComponent :
		public USceneComponent,
		public INavRelevantInterface,
		public IInterface_AsyncCompilation,
		public IPhysicsComponent
	{
	public:
		UE_DEFINE_UOBJECT(UPrimitiveComponent, USceneComponent, "Engine", "PrimitiveComponent");

		class FComponentPSOPrecacheParams;

		using FComponentPSOPrecacheParamsList = TArray<FComponentPSOPrecacheParams, TInlineAllocator<2>>;

		// override
		virtual ~UPrimitiveComponent();  // 000

		// add
		virtual const TArray<URuntimeVirtualTexture*>& GetRuntimeVirtualTextures() const;                                                                                                                                                                                                                                                                                                      //
		virtual ERuntimeVirtualTextureMainPassType     GetVirtualTextureRenderPassType() const;                                                                                                                                                                                                                                                                                                //
		virtual float                                  GetVirtualTextureMainPassMaxDrawDistance() const;                                                                                                                                                                                                                                                                                       //
		virtual bool                                   AreAllCollideableDescendantsRelative(bool a_cache = true);                                                                                                                                                                                                                                                                              //
		virtual void                                   UpdateVisibilityOptims();                                                                                                                                                                                                                                                                                                               //
		virtual void                                   SetupPrecachePSOParams(FPSOPrecacheParams& a_params);                                                                                                                                                                                                                                                                                   //
		virtual void                                   CollectPSOPrecacheData(const FPSOPrecacheParams& a_params, FComponentPSOPrecacheParamsList& a_paramsList);                                                                                                                                                                                                                              //
		virtual void                                   PrecachePSOs();                                                                                                                                                                                                                                                                                                                         //
		virtual bool                                   GetIgnoreBoundsForEditorFocus() const;                                                                                                                                                                                                                                                                                                  //
		virtual bool                                   ComponentOverlapMultiImpl(TArray<FOverlapResult>& a_overlaps, const UWorld* a_world, const FVector& a_position, const FQuat& a_rotation, ECollisionChannel a_channel, const FComponentQueryParams& a_params, const FCollisionObjectQueryParams& a_objectParams) const;                                                                  //
		virtual UMaterialInterface*                    GetMaterial(std::int32_t a_index) const;                                                                                                                                                                                                                                                                                                //
		virtual UMaterialInterface*                    GetEditorMaterial(std::int32_t a_index) const;                                                                                                                                                                                                                                                                                          //
		virtual void                                   SetMaterial(std::int32_t a_index, UMaterialInterface* a_material);                                                                                                                                                                                                                                                                      //
		virtual void                                   SetMaterialByName(FName a_slot, UMaterialInterface* a_material);                                                                                                                                                                                                                                                                        //
		virtual UMaterialInstanceDynamic*              CreateAndSetMaterialInstanceDynamic(std::int32_t a_index);                                                                                                                                                                                                                                                                              //
		virtual UMaterialInstanceDynamic*              CreateAndSetMaterialInstanceDynamicFromMaterial(std::int32_t a_index, UMaterialInterface* a_material);                                                                                                                                                                                                                                  //
		virtual UMaterialInstanceDynamic*              CreateDynamicMaterialInstance(std::int32_t a_index, UMaterialInterface* a_material = nullptr, FName a_slot = EName::None);                                                                                                                                                                                                              //
		virtual UMaterialInterface*                    GetMaterialFromCollisionFaceIndex(std::int32_t a_index, std::int32_t& a_sectionIndex) const;                                                                                                                                                                                                                                            //
		virtual void                                   SetWalkableSlopeOverride(const FWalkableSlopeOverride& a_override);                                                                                                                                                                                                                                                                     //
		virtual void                                   SetSimulatePhysics(bool a_simulate);                                                                                                                                                                                                                                                                                                    //
		virtual bool                                   CanEditSimulatePhysics();                                                                                                                                                                                                                                                                                                               //
		virtual void                                   SetConstraintMode(EDOFMode a_mode);                                                                                                                                                                                                                                                                                                     //
		virtual void                                   AddImpulse(FVector a_impulse, FName a_boneName = EName::None, bool a_velocity = false);                                                                                                                                                                                                                                                 //
		virtual void                                   AddAngularImpulseInRadians(FVector a_impulse, FName a_boneName = EName::None, bool a_velocity = false);                                                                                                                                                                                                                                 //
		virtual void                                   AddImpulseAtLocation(FVector a_impulse, FVector a_location, FName a_boneName = EName::None);                                                                                                                                                                                                                                            //
		virtual void                                   AddVelocityChangeImpulseAtLocation(FVector a_impulse, FVector a_location, FName a_boneName = EName::None);                                                                                                                                                                                                                              //
		virtual void                                   AddRadialImpulse(FVector a_origin, float a_radius, float a_strength, ERadialImpulseFalloff a_falloff, bool a_velocity = false);                                                                                                                                                                                                         //
		virtual void                                   AddForce(FVector a_force, FName a_boneName = EName::None, bool a_acceleration = false);                                                                                                                                                                                                                                                 //
		virtual void                                   AddForceAtLocation(FVector a_force, FVector a_location, FName a_boneName = EName::None);                                                                                                                                                                                                                                                //
		virtual void                                   AddForceAtLocationLocal(FVector a_force, FVector a_location, FName a_boneName = EName::None);                                                                                                                                                                                                                                           //
		virtual void                                   AddRadialForce(FVector a_origin, float a_radius, float a_strength, ERadialImpulseFalloff a_falloff, bool a_acceleration = false);                                                                                                                                                                                                       //
		virtual void                                   AddTorqueInRadians(FVector a_torque, FName a_boneName = EName::None, bool a_acceleration = false);                                                                                                                                                                                                                                      //
		virtual void                                   SetPhysicsLinearVelocity(FVector a_velocity, bool a_add = false, FName a_boneName = EName::None);                                                                                                                                                                                                                                       //
		virtual void                                   SetAllPhysicsLinearVelocity(FVector a_velocity, bool a_add = false);                                                                                                                                                                                                                                                                    //
		virtual void                                   SetPhysicsAngularVelocityInRadians(FVector a_angularVelocity, bool a_add = false, FName a_boneName = EName::None);                                                                                                                                                                                                                      //
		virtual void                                   WakeRigidBody(FName a_boneName = EName::None);                                                                                                                                                                                                                                                                                          //
		virtual void                                   SetNotifyRigidBodyCollision(bool a_value);                                                                                                                                                                                                                                                                                              //
		virtual void                                   SetCollisionEnabled(ECollisionEnabled a_value);                                                                                                                                                                                                                                                                                         //
		virtual void                                   SetCollisionProfileName(FName a_name, bool a_updateOverlaps);                                                                                                                                                                                                                                                                           //
		virtual void                                   SetCollisionObjectType(ECollisionChannel a_channel);                                                                                                                                                                                                                                                                                    //
		virtual bool                                   ShouldRenderSelected() const;                                                                                                                                                                                                                                                                                                           //
		virtual float                                  GetStreamingScale() const;                                                                                                                                                                                                                                                                                                              //
		virtual bool                                   HasValidSettingsForStaticLighting(bool a_overlookInvalidComponents) const;                                                                                                                                                                                                                                                              //
		virtual bool                                   UsesOnlyUnlitMaterials() const;                                                                                                                                                                                                                                                                                                         //
		virtual bool                                   GetLightMapResolution(std::int32_t& a_width, std::int32_t& a_height) const;                                                                                                                                                                                                                                                             //
		virtual std::int32_t                           GetStaticLightMapResolution() const;                                                                                                                                                                                                                                                                                                    //
		virtual void                                   GetLightAndShadowMapMemoryUsage(std::int32_t& a_lightMap, std::int32_t& a_shadowMap) const;                                                                                                                                                                                                                                             //
		virtual ELightMapInteractionType               GetStaticLightingType() const;                                                                                                                                                                                                                                                                                                          //
		virtual void                                   GetStreamingRenderAssetInfo(FStreamingTextureLevelContext& a_context, TArray<FStreamingRenderAssetPrimitiveInfo>& a_assets) const;                                                                                                                                                                                                      //
		virtual bool                                   BuildTextureStreamingDataImpl(ETextureStreamingBuildType a_buildType, EMaterialQualityLevel a_qualityLevel, ERHIFeatureLevel a_featureLevel, TSet<FGuid>& a_resources, bool& a_support);                                                                                                                                                //
		virtual ESceneDepthPriorityGroup               GetStaticDepthPriorityGroup() const;                                                                                                                                                                                                                                                                                                    //
		virtual void                                   GetUsedMaterials(TArray<UMaterialInterface*>& a_materials, bool a_debug = false);                                                                                                                                                                                                                                                       //
		virtual void                                   GetUsedTextures(TArray<UTexture*>& a_textures, EMaterialQualityLevel a_qualityLevel);                                                                                                                                                                                                                                                   //
		virtual UBodySetup*                            GetBodySetup();                                                                                                                                                                                                                                                                                                                         //
		virtual FMatrix                                GetRenderMatrix() const;                                                                                                                                                                                                                                                                                                                //
		virtual std::int32_t                           GetNumMaterials() const;                                                                                                                                                                                                                                                                                                                //
		virtual FBodyInstance*                         GetBodyInstance(FName a_boneName = EName::None, bool a_welded = true, std::int32_t a_index = INDEX_NONE) const;                                                                                                                                                                                                                         //
		virtual bool                                   GetSquaredDistanceToCollision(const FVector& a_point, float& a_squaredDistance, FVector& a_pointClosest) const;                                                                                                                                                                                                                         //
		virtual FPrimitiveSceneProxy*                  CreateSceneProxy();                                                                                                                                                                                                                                                                                                                     //
		virtual bool                                   ShouldRecreateProxyOnUpdateTransform() const;                                                                                                                                                                                                                                                                                           //
		virtual bool                                   IsZeroExtent() const;                                                                                                                                                                                                                                                                                                                   //
		virtual void                                   ReceiveComponentDamage(float a_damage, const FDamageEvent& a_event, AController* a_eventInstigator, AActor* a_cause);                                                                                                                                                                                                                   //
		virtual void                                   WeldTo(USceneComponent* a_parent, FName a_socket = EName::None);                                                                                                                                                                                                                                                                        //
		virtual bool                                   WeldToImplementation(USceneComponent* a_parent, FName a_socket = EName::None, bool a_child = true);                                                                                                                                                                                                                                     //
		virtual void                                   UnWeldFromParent();                                                                                                                                                                                                                                                                                                                     //
		virtual void                                   UnWeldChildren();                                                                                                                                                                                                                                                                                                                       //
		virtual void                                   GetWeldedBodies(TArray<FBodyInstance*>& a_bodies, TArray<FName>& a_labels, bool a_includeAuto = false);                                                                                                                                                                                                                                 //
		virtual FTransform                             GetComponentTransformFromBodyInstance(FBodyInstance* a_root);                                                                                                                                                                                                                                                                           //
		virtual bool                                   IsShown(const FEngineShowFlags& a_flags) const;                                                                                                                                                                                                                                                                                         //
		virtual bool                                   SupportsWorldPositionOffsetVelocity() const;                                                                                                                                                                                                                                                                                            //
		virtual bool                                   SupportsStaticLighting() const;                                                                                                                                                                                                                                                                                                         //
		virtual void                                   UpdatePhysicsToRBChannels();                                                                                                                                                                                                                                                                                                            //
		virtual bool                                   ShouldDispatchWakeEvents(FName a_boneName) const;                                                                                                                                                                                                                                                                                       //
		virtual void                                   InitSweepCollisionParams(FCollisionQueryParams& a_queryParams, FCollisionResponseParams& a_responseParams) const;                                                                                                                                                                                                                       //
		virtual FCollisionShape*                       GetCollisionShape(float a_inflation = 0.0F) const;                                                                                                                                                                                                                                                                                      //
		virtual bool                                   AreSymmetricRotations(const FQuat& a_quatA, const FQuat a_quatB, const FVector& a_scale3D) const;                                                                                                                                                                                                                                       //
		virtual void                                   PushSelectionToProxy();                                                                                                                                                                                                                                                                                                                 //
		virtual float                                  GetEmissiveBoost(std::int32_t a_elementIndex) const;                                                                                                                                                                                                                                                                                    //
		virtual float                                  GetDiffuseBoost(std::int32_t a_elementIndex) const;                                                                                                                                                                                                                                                                                     //
		virtual bool                                   GetShadowIndirectOnly() const;                                                                                                                                                                                                                                                                                                          //
		virtual bool                                   IsCompiling() const;                                                                                                                                                                                                                                                                                                                    //
		virtual void                                   SetAllPhysicsAngularVelocityInRadians(const FVector& a_velocity, bool a_add = false);                                                                                                                                                                                                                                                   //
		virtual void                                   SetAllPhysicsPosition(FVector a_position);                                                                                                                                                                                                                                                                                              //
		virtual void                                   SetAllPhysicsRotation(const FQuat& a_rotation);                                                                                                                                                                                                                                                                                         //
		virtual void                                   SetAllPhysicsRotation(FRotator a_rotation);                                                                                                                                                                                                                                                                                             //
		virtual void                                   WakeAllRigidBodies();                                                                                                                                                                                                                                                                                                                   //
		virtual void                                   SetEnableGravity(bool a_value);                                                                                                                                                                                                                                                                                                         //
		virtual bool                                   IsGravityEnabled() const;                                                                                                                                                                                                                                                                                                               //
		virtual void                                   SetLinearDamping(float a_value);                                                                                                                                                                                                                                                                                                        //
		virtual float                                  GetLinearDamping() const;                                                                                                                                                                                                                                                                                                               //
		virtual void                                   SetAngularDamping(float a_value);                                                                                                                                                                                                                                                                                                       //
		virtual float                                  GetAngularDamping() const;                                                                                                                                                                                                                                                                                                              //
		virtual void                                   SetMassScale(FName a_boneName = EName::None, float a_value = 1.0F);                                                                                                                                                                                                                                                                     //
		virtual float                                  GetMassScale(FName a_boneName = EName::None) const;                                                                                                                                                                                                                                                                                     //
		virtual void                                   SetAllMassScale(float a_value = 1.0F);                                                                                                                                                                                                                                                                                                  //
		virtual void                                   SetMassOverrideInKg(FName a_boneName = EName::None, float a_value = 1.0F, bool a_override = true);                                                                                                                                                                                                                                      //
		virtual float                                  GetMass() const;                                                                                                                                                                                                                                                                                                                        //
		virtual FVector                                GetInertiaTensor(FName a_boneName = EName::None) const;                                                                                                                                                                                                                                                                                 //
		virtual FVector                                ScaleByMomentOfInertia(FVector a_vector, FName a_boneName = EName::None) const;                                                                                                                                                                                                                                                         //
		virtual float                                  CalculateMass(FName a_boneName = EName::None);                                                                                                                                                                                                                                                                                          //
		virtual void                                   SetUseCCD(bool a_value, FName a_boneName = EName::None);                                                                                                                                                                                                                                                                                //
		virtual void                                   SetAllUseCCD(bool a_value);                                                                                                                                                                                                                                                                                                             //
		virtual void                                   PutAllRigidBodiesToSleep();                                                                                                                                                                                                                                                                                                             //
		virtual bool                                   IsAnyRigidBodyAwake();                                                                                                                                                                                                                                                                                                                  //
		virtual void                                   SetCollisionResponseToChannel(ECollisionChannel a_channel, ECollisionResponse a_response);                                                                                                                                                                                                                                              //
		virtual void                                   SetCollisionResponseToAllChannels(ECollisionResponse a_response);                                                                                                                                                                                                                                                                       //
		virtual void                                   SetCollisionResponseToChannels(const FCollisionResponseContainer& a_response);                                                                                                                                                                                                                                                          //
		virtual void                                   OnComponentCollisionSettingsChanged(bool a_updateOverlaps);                                                                                                                                                                                                                                                                             //
		virtual void                                   OnGenerateOverlapEventsChanged();                                                                                                                                                                                                                                                                                                       //
		virtual void                                   SetPhysMaterialOverride(UPhysicalMaterial* a_material);                                                                                                                                                                                                                                                                                 //
		virtual bool                                   LineTraceComponent(FHitResult& a_hit, const FVector a_start, const FVector a_end, ECollisionChannel a_channel, const FCollisionQueryParams& a_params, const FCollisionResponseParams& a_responseParams, const FCollisionObjectQueryParams& a_objectParams);                                                                             //
		virtual bool                                   LineTraceComponent(FHitResult& a_hit, const FVector a_start, const FVector a_end, const FCollisionQueryParams& a_params);                                                                                                                                                                                                               //
		virtual bool                                   SweepComponent(FHitResult& a_hit, const FVector a_start, const FVector a_end, const FQuat& a_shapeWorldRotation, const FPhysicsGeometry& a_geometry, ECollisionChannel a_channel, const FCollisionQueryParams& a_params, const FCollisionResponseParams& a_responseParams, const FCollisionObjectQueryParams& a_objectParams);          //
		virtual bool                                   SweepComponent(FHitResult& a_hit, const FVector a_start, const FVector a_end, const FQuat& a_shapeWorldRotation, const FCollisionShape& a_collisionShape, bool a_complex = false);                                                                                                                                                      //
		virtual bool                                   ComponentOverlapComponentImpl(UPrimitiveComponent* a_component, const FVector a_position, const FQuat& a_rotation, const FCollisionQueryParams& a_params);                                                                                                                                                                              //
		virtual bool                                   ComponentOverlapComponentWithResultImpl(const UPrimitiveComponent* a_component, const FVector& a_position, const FQuat& a_rotation, const FCollisionQueryParams& a_params, TArray<FOverlapResult>& a_overlaps) const;                                                                                                                   //
		virtual bool                                   OverlapComponent(const FVector& a_position, const FQuat& a_rotation, const FCollisionShape& a_collisionShape) const;                                                                                                                                                                                                                    //
		virtual bool                                   OverlapComponent(const FVector& a_position, const FQuat& a_rotation, const FCollisionShape& a_collisionShape);                                                                                                                                                                                                                          //
		virtual bool                                   OverlapComponentWithResult(const FVector& a_position, const FQuat& a_rotation, const FPhysicsGeometry& a_geometry, ECollisionChannel a_channel, const FCollisionQueryParams& a_params, const FCollisionResponseParams& a_responseParams, const FCollisionObjectQueryParams& a_objectParams, TArray<FOverlapResult>& a_overlaps) const;  //
		virtual bool                                   OverlapComponentWithResult(const FVector& a_position, const FQuat& a_rotation, const FCollisionShape& a_collisionShape, TArray<FOverlapResult>& a_overlaps) const;                                                                                                                                                                      //
		virtual bool                                   ComputePenetration(FMTDResult& a_mtd, const FCollisionShape& a_collisionShape, const FVector& a_position, const FQuat& a_rotation);                                                                                                                                                                                                     //
		virtual bool                                   CanCharacterStepUp(APawn* a_pawn) const;                                                                                                                                                                                                                                                                                                //
		virtual bool                                   DoCustomNavigableGeometryExport(FNavigableGeometryExport& a_export) const;                                                                                                                                                                                                                                                              //

		// members
		float                                       minDrawDistance;                             // 2B8
		float                                       ldMaxDrawDistance;                           // 2BC
		float                                       cachedMaxDrawDistance;                       // 2C0
		TEnumAsByte<ESceneDepthPriorityGroup>       depthPriorityGroup;                          // 2C4
		TEnumAsByte<ESceneDepthPriorityGroup>       viewOwnerDepthPriorityGroup;                 // 2C5
		TEnumAsByte<EIndirectLightingCacheQuality>  indirectLightingCacheQuality;                // 2C6
		ELightmapType                               lightmapType;                                // 2C7
		EHLODBatchingPolicy                         hlodBatchingPolicy;                          // 2C8
		std::uint8_t                                enableAutoLODGeneration: 1;                  // 2C9:0
		std::uint8_t                                isActorTextureStreamingBuiltData: 1;         // 2C9:1
		std::uint8_t                                isValidTextureStreamingBuiltData: 1;         // 2C9:2
		std::uint8_t                                neverDistanceCull: 1;                        // 2C9:3
		std::uint8_t                                attachedToStreamingManagerAsStatic: 1;       // 2C9:4
		std::uint8_t                                attachedToStreamingManagerAsDynamic: 1;      // 2C9:5
		std::uint8_t                                handledByStreamingManagerAsDynamic: 1;       // 2C9:6
		std::uint8_t                                ignoreStreamingManagerUpdate: 1;             // 2C9:7
		std::uint8_t                                attachedToCoarseMeshStreamingManager: 1;     // 2CA:0
		std::uint8_t                                bulkReregister: 1;                           // 2CA:1
		std::uint8_t                                alwaysCreatePhysicsState: 1;                 // 2CA:2
		bool                                        forceDrawDebugWireframe;                     // 2CB
		std::uint8_t                                generateOverlapEvents: 1;                    // 2CC:0
		std::uint8_t                                multiBodyOverlap: 1;                         // 2CC:1
		std::uint8_t                                traceComplexOnMove: 1;                       // 2CC:2
		std::uint8_t                                returnMaterialOnMove: 1;                     // 2CC:3
		std::uint8_t                                useViewOwnerDepthPriorityGroup: 1;           // 2CC:4
		std::uint8_t                                allowCullDistanceVolume: 1;                  // 2CC:5
		std::uint8_t                                visibleInReflectionCaptures: 1;              // 2CC:6
		std::uint8_t                                visibleInRealTimeSkyCaptures: 1;             // 2CC:7
		std::uint8_t                                visibleInRayTracing: 1;                      // 2CD:0
		std::uint8_t                                renderInMainPass: 1;                         // 2CD:1
		std::uint8_t                                renderInDepthPass: 1;                        // 2CD:2
		std::uint8_t                                receivesDecals: 1;                           // 2CD:3
		std::uint8_t                                holdout: 1;                                  // 2CD:4
		std::uint8_t                                ownerNoSee: 1;                               // 2CD:5
		std::uint8_t                                onlyOwnerSee: 1;                             // 2CD:6
		std::uint8_t                                treatAsBackgroundForOcclusion: 1;            // 2CD:7
		std::uint8_t                                useAsOccluder: 1;                            // 2CE:0
		std::uint8_t                                selectable: 1;                               // 2CE:1
		std::uint8_t                                forceMipStreaming: 1;                        // 2CE:2
		std::uint8_t                                hasPerInstanceHitProxies: 1;                 // 2CE:3
		std::uint8_t                                castShadow: 1;                               // 2CE:4
		std::uint8_t                                emissiveLightSource: 1;                      // 2CE:5
		std::uint8_t                                affectDynamicIndirectLighting: 1;            // 2CE:6
		std::uint8_t                                affectIndirectLightingWhileHidden: 1;        // 2CE:7
		std::uint8_t                                affectDistanceFieldLighting: 1;              // 2CF:0
		std::uint8_t                                castDynamicShadow: 1;                        // 2CF:1
		std::uint8_t                                castStaticShadow: 1;                         // 2CF:2
		EShadowCacheInvalidationBehavior            shadowCacheInvalidationBehavior;             // 2D0
		std::uint8_t                                castVolumetricTranslucentShadow: 1;          // 2D1:0
		std::uint8_t                                castContactShadow: 1;                        // 2D1:1
		std::uint8_t                                selfShadowOnly: 1;                           // 2D1:2
		std::uint8_t                                castFarShadow: 1;                            // 2D1:3
		std::uint8_t                                castInsetShadow: 1;                          // 2D1:4
		std::uint8_t                                castCinematicShadow: 1;                      // 2D1:5
		std::uint8_t                                castHiddenShadow: 1;                         // 2D1:6
		std::uint8_t                                castShadowAsTwoSided: 1;                     // 2D1:7
		std::uint8_t                                lightAsIfStatic_DEPRECATED: 1;               // 2D2:0
		std::uint8_t                                lightAttachmentsAsGroup: 1;                  // 2D2:1
		std::uint8_t                                excludeFromLightAttachmentGroup: 1;          // 2D2:2
		std::uint8_t                                receiveMobileCSMShadows: 1;                  // 2D2:3
		std::uint8_t                                singleSampleShadowFromStationaryLights: 1;   // 2D2:4
		std::uint8_t                                ignoreRadialImpulse: 1;                      // 2D2:5
		std::uint8_t                                ignoreRadialForce: 1;                        // 2D2:6
		std::uint8_t                                applyImpulseOnDamage: 1;                     // 2D2:7
		std::uint8_t                                replicatePhysicsToAutonomousProxy: 1;        // 2D3:0
		std::uint8_t                                fillCollisionUnderneathForNavmesh: 1;        // 2D3:1
		std::uint8_t                                alwaysLoadOnClient: 1;                       // 2D3:2
		std::uint8_t                                alwaysLoadOnServer: 1;                       // 2D3:3
		std::uint8_t                                useEditorCompositing: 1;                     // 2D3:4
		std::uint8_t                                isBeingMovedByEditor: 1;                     // 2D3:5
		std::uint8_t                                renderCustomDepth: 1;                        // 2D3:6
		std::uint8_t                                visibleInSceneCaptureOnly: 1;                // 2D3:7
		std::uint8_t                                hiddenInSceneCapture: 1;                     // 2D4:0
		std::uint8_t                                rayTracingFarField: 1;                       // 2D4:1
		std::uint8_t                                cachedAllCollideableDescendantsRelative: 1;  // 2D4:2
		std::uint8_t                                hasNoStreamableTextures: 1;                  // 2D4:3
		std::uint8_t                                staticWhenNotMoveable: 1;                    // 2D4:4
		std::uint8_t                                psoPrecacheCalled: 1;                        // 2D4:5
		std::uint8_t                                psoPrecacheRequestBoosted: 1;                // 2D4:6
		TArray<std::uint32_t>                       materialPSOPrecacheRequestIDs;               // 2D8
		TRefCountPtr<FGraphEvent>                   psoPrecacheCompileEvent;                     // 2E8
		std::uint8_t                                ignoreBoundsForEditorFocus: 1;               // 2F0:0
		std::uint8_t                                forceIgnoreOcclusion: 1;                     // 2F0:1
		TEnumAsByte<EHasCustomNavigableGeometry>    hasCustomNavigableGeometry;                  // 2F1
		std::uint8_t                                moveIgnoreMask;                              // 2F2
		TEnumAsByte<ECanBeCharacterBase>            canCharacterStepUpOn;                        // 2F3
		FLightingChannels                           lightingChannels;                            // 2F4
		EDecalChannels                              decalChannels;                               // 2F5
		bool                                        doDither;                                    // 2F6
		float                                       ditherScale;                                 // 2F8
		std::int32_t                                rayTracingGroupId;                           // 2FC
		std::int32_t                                visibilityId;                                // 300
		std::int32_t                                customDepthStencilValue;                     // 304
		FCustomPrimitiveData                        customPrimitiveData;                         // 308
		FCustomPrimitiveData                        customPrimitiveDataInternal;                 // 318
		FPhysScene_Chaos*                           deferredCreatePhysicsStateScene;             // 328
		std::int32_t                                translucencySortPriority;                    // 330
		float                                       translucencySortDistanceOffset;              // 334
		TArray<TObjectPtr<URuntimeVirtualTexture>>  runtimeVirtualTextures;                      // 338
		char                                        virtualTextureLodBias;                       // 348
		char                                        virtualTextureCullMips;                      // 349
		char                                        virtualTextureMinCoverage;                   // 34A
		ERuntimeVirtualTextureMainPassType          virtualTextureRenderPassType;                // 34B
		FPrimitiveComponentId                       componentId;                                 // 34C
		std::int32_t                                registrationSerialNumber;                    // 350
		FThreadSafeCounter                          attachmentCounter;                           // 354
		float                                       lastCheckedAllCollideableDescendantsTime;    // 358
		float                                       boundsScale;                                 // 35C
		float                                       lastSubmitTime;                              // 360
		float                                       lastRenderTime;                              // 364
		float                                       lastRenderTimeOnScreen;                      // 368
		float                                       lastOcclusionTime;                           // 36C
		float                                       lastNotOccludedTime;                         // 370
		float                                       occlusionBoundsSlack;                        // 374
		TArray<TObjectPtr<AActor>>                  moveIgnoreActors;                            // 378
		TArray<TObjectPtr<UPrimitiveComponent>>     moveIgnoreComponents;                        // 388
		TArray<FOverlapInfo>                        overlappingComponents;                       // 398
		std::byte                                   bodyInstance[0x190];                         // 3A8 - FBodyInstance
		FComponentHitSignature                      onComponentHit;                              // 538
		FComponentBeginOverlapSignature             onComponentBeginOverlap;                     // 539
		FComponentEndOverlapSignature               onComponentEndOverlap;                       // 53A
		FComponentWakeSignature                     onComponentWake;                             // 53B
		FComponentSleepSignature                    onComponentSleep;                            // 53C
		FComponentCollisionSettingsChangedSignature onComponentCollisionSettingsChangedEvent;    // 53D
		FComponentPhysicsStateChanged               onComponentPhysicsStateChanged;              // 53E
		FComponentBeginCursorOverSignature          onBeginCursorOver;                           // 53F
		FComponentEndCursorOverSignature            onEndCursorOver;                             // 540
		FComponentOnClickedSignature                onClicked;                                   // 541
		FComponentOnReleasedSignature               onReleased;                                  // 542
		FComponentOnInputTouchBeginSignature        onInputTouchBegin;                           // 543
		FComponentOnInputTouchEndSignature          onInputTouchEnd;                             // 544
		FComponentBeginTouchOverSignature           onInputTouchEnter;                           // 545
		FComponentEndTouchOverSignature             onInputTouchLeave;                           // 546
		ERayTracingGroupCullingPriority             rayTracingGroupCullingPriority;              // 547
		ERendererStencilMask                        customDepthStencilWriteMask;                 // 548
		FPrimitiveSceneProxy*                       sceneProxy;                                  // 550
		FRenderCommandFence                         detachFence;                                 // 558
		std::uint8_t                                excludeFromHLODLevels;                       // 568
		TObjectPtr<UPrimitiveComponent>             lodParentPrimitive;                          // 570
	};
	static_assert(sizeof(UPrimitiveComponent) == 0x580);
}
