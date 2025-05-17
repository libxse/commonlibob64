#pragma once

#include "UE/E/EClassFlags.h"
#include "UE/E/EClassCastFlags.h"

#define UE_DECLARE_TCASTFLAGS(a_class)                                 \
	class a_class;                                                     \
	template <>                                                        \
	struct TCastFlags<a_class>                                         \
	{                                                                  \
		static const EClassCastFlags Value = EClassCastFlags::a_class; \
	};                                                                 \
	template <>                                                        \
	struct TCastFlags<const a_class>                                   \
	{                                                                  \
		static const EClassCastFlags Value = EClassCastFlags::a_class; \
	};

namespace UE
{
	class UObject;

	template <class T, bool B = std::is_convertible_v<T*, const volatile UObject*>>
	struct TIsIInterface
	{
		static constexpr bool Value{ false };
	};

	template <class T>
	struct TIsIInterface<T, false>
	{
		template <class U>
		static char (&Resolve(typename U::UClassType*))[(U::CLASS_TYPE::CLASS_FLAGS & EClassFlags::Interface) ? 2 : 1];
		template <class U>
		static char (&Resolve(...))[1];

		static constexpr bool Value{ sizeof(Resolve<T>(0)) - 1 };
	};

	template <class>
	struct TCastFlags
	{
		static const EClassCastFlags Value = EClassCastFlags::None;
	};

	UE_DECLARE_TCASTFLAGS(UField)
	UE_DECLARE_TCASTFLAGS(UEnum)
	UE_DECLARE_TCASTFLAGS(UStruct)
	UE_DECLARE_TCASTFLAGS(UScriptStruct)
	UE_DECLARE_TCASTFLAGS(UClass)
	UE_DECLARE_TCASTFLAGS(FProperty)
	UE_DECLARE_TCASTFLAGS(FObjectPropertyBase)
	UE_DECLARE_TCASTFLAGS(FObjectProperty)
	UE_DECLARE_TCASTFLAGS(FObjectPtrProperty)
	UE_DECLARE_TCASTFLAGS(FWeakObjectProperty)
	UE_DECLARE_TCASTFLAGS(FLazyObjectProperty)
	UE_DECLARE_TCASTFLAGS(FSoftObjectProperty)
	UE_DECLARE_TCASTFLAGS(FSoftClassProperty)
	UE_DECLARE_TCASTFLAGS(FBoolProperty)
	UE_DECLARE_TCASTFLAGS(UFunction)
	UE_DECLARE_TCASTFLAGS(FStructProperty)
	UE_DECLARE_TCASTFLAGS(FByteProperty)
	UE_DECLARE_TCASTFLAGS(FIntProperty)
	UE_DECLARE_TCASTFLAGS(FFloatProperty)
	UE_DECLARE_TCASTFLAGS(FDoubleProperty)
	UE_DECLARE_TCASTFLAGS(FClassProperty)
	UE_DECLARE_TCASTFLAGS(FInterfaceProperty)
	UE_DECLARE_TCASTFLAGS(FNameProperty)
	UE_DECLARE_TCASTFLAGS(FStrProperty)
	UE_DECLARE_TCASTFLAGS(FTextProperty)
	UE_DECLARE_TCASTFLAGS(FArrayProperty)
	UE_DECLARE_TCASTFLAGS(FDelegateProperty)
	UE_DECLARE_TCASTFLAGS(FMulticastDelegateProperty)
	UE_DECLARE_TCASTFLAGS(UPackage)
	UE_DECLARE_TCASTFLAGS(ULevel)
	UE_DECLARE_TCASTFLAGS(AActor)
	UE_DECLARE_TCASTFLAGS(APlayerController)
	UE_DECLARE_TCASTFLAGS(APawn)
	UE_DECLARE_TCASTFLAGS(USceneComponent)
	UE_DECLARE_TCASTFLAGS(UPrimitiveComponent)
	UE_DECLARE_TCASTFLAGS(USkinnedMeshComponent)
	UE_DECLARE_TCASTFLAGS(USkeletalMeshComponent)
	UE_DECLARE_TCASTFLAGS(UBlueprint);
	UE_DECLARE_TCASTFLAGS(UDelegateFunction);
	UE_DECLARE_TCASTFLAGS(UStaticMeshComponent);
	UE_DECLARE_TCASTFLAGS(FEnumProperty)
	UE_DECLARE_TCASTFLAGS(FNumericProperty)
	UE_DECLARE_TCASTFLAGS(FInt8Property)
	UE_DECLARE_TCASTFLAGS(FInt16Property)
	UE_DECLARE_TCASTFLAGS(FInt64Property)
	UE_DECLARE_TCASTFLAGS(FUInt16Property)
	UE_DECLARE_TCASTFLAGS(FUInt32Property)
	UE_DECLARE_TCASTFLAGS(FUInt64Property)
	UE_DECLARE_TCASTFLAGS(FMapProperty)
	UE_DECLARE_TCASTFLAGS(FSetProperty)
	UE_DECLARE_TCASTFLAGS(USparseDelegateFunction)
	UE_DECLARE_TCASTFLAGS(FMulticastInlineDelegateProperty)
	UE_DECLARE_TCASTFLAGS(FMulticastSparseDelegateProperty)
	UE_DECLARE_TCASTFLAGS(FOptionalProperty)
}

#undef UE_DECLARE_TCASTFLAGS
