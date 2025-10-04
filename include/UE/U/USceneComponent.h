#pragma once

#include "UE/E/ECollisionChannel.h"
#include "UE/E/ECollisionEnabled.h"
#include "UE/E/ECollisionResponse.h"
#include "UE/E/EComponentMobility.h"
#include "UE/E/EDetailMode.h"
#include "UE/E/EMoveComponentFlags.h"
#include "UE/E/ERelativeTransformSpace.h"
#include "UE/E/ETeleportType.h"
#include "UE/E/EUpdateTransformFlags.h"
#include "UE/F/FBoxSphereBounds.h"
#include "UE/F/FComponentSocketDescription.h"
#include "UE/F/FRotationConversionCache.h"
#include "UE/F/FRotator.h"
#include "UE/F/FTransform.h"
#include "UE/T/TArrayView.h"
#include "UE/T/TBaseDynamicMulticastDelegate.h"
#include "UE/T/TMulticastDelegate.h"
#include "UE/T/TSparseDynamicDelegate.h"
#include "UE/U/UActorComponent.h"

namespace UE
{
	class APhysicsVolume;
	class FCollisionResponseContainer;
	class FDetachmentTransformRules;
	class FHitResult;
	class FIsRootComponentChangedInfoGetter;
	class FLevelCollection;
	class FOverlapInfo;
	class FPhysicsVolumeChangedInfoGetter;
	class FScopedMovementUpdate;
	class USceneComponent;

	using FIsRootComponentChanged_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, USceneComponent*, bool>;
	using FIsRootComponentChanged = TSparseDynamicDelegate<FIsRootComponentChanged_MCSignature, USceneComponent, FIsRootComponentChangedInfoGetter>;
	using FPhysicsVolumeChanged_MCSignature = TBaseDynamicMulticastDelegate<FNotThreadSafeDelegateMode, void, APhysicsVolume*>;
	using FPhysicsVolumeChanged = TSparseDynamicDelegate<FPhysicsVolumeChanged_MCSignature, USceneComponent, FPhysicsVolumeChangedInfoGetter>;
	using FTransformUpdated = TMulticastDelegate<void(USceneComponent*, EUpdateTransformFlags, ETeleportType)>;
	using TOverlapArrayView = TArrayView<const FOverlapInfo>;

	class USceneComponent :
		public UActorComponent
	{
	public:
		UE_DEFINE_UOBJECT(USceneComponent, UActorComponent, "Engine", "SceneComponent");

		// override
		virtual ~USceneComponent();  // 000

		// add
		virtual bool                               IsSimulatingPhysics(FName a_boneName = EName::None) const;                                                                                                                         // 093
		virtual bool                               IsAnySimulatingPhysics() const;                                                                                                                                                    // 094
		virtual void                               DetachFromParent(bool a_maintainWorldPosition = false, bool a_callModify = true);                                                                                                  // 095
		virtual void                               DetachFromComponent(const FDetachmentTransformRules& a_rules);                                                                                                                     // 096
		virtual FTransform                         GetSocketTransform(FName a_socketName, ERelativeTransformSpace a_transformSpace) const;                                                                                            // 097
		virtual FVector                            GetSocketLocation(FName a_socketName) const;                                                                                                                                       // 098
		virtual FRotator                           GetSocketRotation(FName a_socketName) const;                                                                                                                                       // 099
		virtual FQuat                              GetSocketQuaternion(FName a_socketName) const;                                                                                                                                     // 09A
		virtual bool                               DoesSocketExist(FName a_socketName) const;                                                                                                                                         // 09B
		virtual bool                               HasAnySockets() const;                                                                                                                                                             // 09C
		virtual void                               QuerySupportedSockets(TArray<FComponentSocketDescription>& a_sockets) const;                                                                                                       // 09D
		virtual FVector                            GetComponentVelocity() const;                                                                                                                                                      // 09E
		virtual bool                               IsVisible() const;                                                                                                                                                                 // 09F
		virtual void                               OnVisibilityChanged();                                                                                                                                                             // 0A0
		virtual void                               OnHiddenInGameChanged();                                                                                                                                                           // 0A1
		virtual void                               OnUpdateTransform(EUpdateTransformFlags a_flags, ETeleportType a_teleport = ETeleportType::None);                                                                                  // 0A2
		virtual bool                               UpdateOverlapsImpl(const TOverlapArrayView* a_pending = nullptr, bool a_notify = true, const TOverlapArrayView* a_endLocation = nullptr);                                          // 0A3
		virtual bool                               MoveComponentImpl(const FVector& a_delta, const FQuat& a_rotation, bool a_sweep, FHitResult* a_hit, EMoveComponentFlags a_flags, ETeleportType a_teleport = ETeleportType::None);  // 0A4
		virtual void                               OnAttachmentChanged();                                                                                                                                                             // 0A5
		virtual FBoxSphereBounds                   CalcBounds(const FTransform& a_localToWorld) const;                                                                                                                                // 0A6
		virtual FBoxSphereBounds                   CalcLocalBounds() const;                                                                                                                                                           // 0A7
		virtual void                               CalcBoundingCylinder(float& a_radius, float& a_halfHeight) const;                                                                                                                  // 0A8
		virtual void                               UpdateBounds();                                                                                                                                                                    // 0A9
		virtual bool                               ShouldCollideWhenPlacing() const;                                                                                                                                                  // 0AA
		virtual void                               UpdatePhysicsVolume(bool a_trigger);                                                                                                                                               // 0AB
		virtual const FCollisionResponseContainer& GetCollisionResponseToChannels() const;                                                                                                                                            // 0AC
		virtual bool                               IsVisibleInEditor() const;                                                                                                                                                         // 0AD
		virtual bool                               IsWorldGeometry() const;                                                                                                                                                           // 0AE
		virtual ECollisionEnabled                  GetCollisionEnabled() const;                                                                                                                                                       // 0AF
		virtual ECollisionResponse                 GetCollisionResponseToChannel(ECollisionChannel a_channel) const;                                                                                                                  // 0B0
		virtual ECollisionChannel                  GetCollisionObjectType() const;                                                                                                                                                    // 0B1
		virtual void                               SetMobility(EComponentMobility a_mobility);                                                                                                                                        // 0B2
		virtual bool                               CanAttachAsChild(const USceneComponent* a_component, FName a_socketName) const;                                                                                                    // 0B3
		virtual FBoxSphereBounds                   GetPlacementExtent() const;                                                                                                                                                        // 0B4
		virtual void                               OnChildAttached(USceneComponent* a_component);                                                                                                                                     // 0B5
		virtual void                               OnChildDetached(USceneComponent* a_component);                                                                                                                                     // 0B6
		virtual bool                               CanHaveStaticMobility() const;                                                                                                                                                     // 0B7
		virtual void                               PropagateLightingScenarioChange();                                                                                                                                                 // 0B8
		virtual bool                               IsPrecomputedLightingValid() const;                                                                                                                                                // 0B9

		// members
		const FLevelCollection*             cachedLevelCollection;                        // 0A0
		TWeakObjectPtr<APhysicsVolume>      physicsVolume;                                // 0A8
		TObjectPtr<USceneComponent>         attachParent;                                 // 0B0
		FName                               attachSocketName;                             // 0B8
		TArray<TObjectPtr<USceneComponent>> attachChildren;                               // 0C0
		TArray<TObjectPtr<USceneComponent>> clientAttachedChildren;                       // 0D0
		FName                               netOldAttachSocketName;                       // 0E0
		USceneComponent*                    netOldAttachParent;                           // 0E8
		FBoxSphereBounds                    bounds;                                       // 0F0
		FVector                             relativeLocation;                             // 128
		FRotator                            relativeRotation;                             // 140
		FVector                             relativeScale3D;                              // 158
		FVector                             componentVelocity;                            // 170
		std::uint8_t                        componentToWorldUpdated: 1;                   // 188:0
		std::uint8_t                        skipUpdateOverlaps: 1;                        // 188:1
		std::uint8_t                        absoluteLocation: 1;                          // 188:2
		std::uint8_t                        absoluteRotation: 1;                          // 188:3
		std::uint8_t                        absoluteScale: 1;                             // 188:4
		std::uint8_t                        visible: 1;                                   // 188:5
		std::uint8_t                        shouldBeAttached: 1;                          // 188:6
		std::uint8_t                        shouldSnapLocationWhenAttached: 1;            // 188:7
		std::uint8_t                        shouldSnapRotationWhenAttached: 1;            // 189:0
		std::uint8_t                        shouldSnapScaleWhenAttached: 1;               // 189:1
		std::uint8_t                        shouldUpdatePhysicsVolume: 1;                 // 189:2
		std::uint8_t                        hiddenInGame: 1;                              // 189:3
		std::uint8_t                        boundsChangeTriggersStreamingDataRebuild: 1;  // 189:4
		std::uint8_t                        useAttachParentBound: 1;                      // 189:5
		std::uint8_t                        computeFastLocalBounds: 1;                    // 189:6
		std::uint8_t                        computeBoundsOnceForGame: 1;                  // 189:7
		std::uint8_t                        computedBoundsOnceForGame: 1;                 // 18A:0
		bool                                doesSkipOverlapUpdateFromAttachedParent;      // 18B
		std::uint8_t                        isNotRenderAttachmentRoot: 1;                 // 18C:0
		std::uint8_t                        disableDetachmentUpdateOverlaps: 1;           // 18C:1
		std::uint8_t                        wantsOnUpdateTransform: 1;                    // 18C:2
		std::uint8_t                        netUpdateTransform: 1;                        // 18C:3
		std::uint8_t                        netUpdateAttachment: 1;                       // 18C:4
		TEnumAsByte<EComponentMobility>     mobility;                                     // 18D
		TEnumAsByte<EDetailMode>            detailMode;                                   // 18E
		FPhysicsVolumeChanged               physicsVolumeChangedDelegate;                 // 18F
		FIsRootComponentChanged             isRootComponentChanged;                       // 190
		FTransformUpdated                   transformUpdated;                             // 198
		TArray<FScopedMovementUpdate*>      scopedMovementStack;                          // 1B0
		FRotationConversionCache            worldRotationCache;                           // 1C0
		FRotationConversionCache            relativeRotationCache;                        // 200
		FTransform                          componentToWorld;                             // 240
	};
	static_assert(sizeof(USceneComponent) == 0x2A0);
}
