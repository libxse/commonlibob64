#pragma once

#include "UE/F/FStaticConstructObjectParameters.h"

namespace UE
{
	class UClass;
	class UObject;
	class UPackage;

	inline UPackage* GetTransientPackage()
	{
		using func_t = UPackage* (*)();
		static REL::Relocation<func_t> func{ ID::GetTransientPackage };
		return func();
	}

	inline UObject* StaticConstructObject_Internal(const FStaticConstructObjectParameters& a_params)
	{
		using func_t = UObject* (*)(const FStaticConstructObjectParameters&);
		static REL::Relocation<func_t> func{ ID::StaticConstructObject_Internal };
		return func(a_params);
	}

	inline UObject* StaticFindObject(UClass* a_class, UObject* a_outer, const wchar_t* a_name, bool a_exactClass = false)
	{
		using func_t = UObject* (*)(UClass*, UObject*, const wchar_t*, bool);
		static REL::Relocation<func_t> func{ ID::StaticFindObject };
		return func(a_class, a_outer, a_name, a_exactClass);
	}

	template <class T>
	inline T* StaticFindObject(UClass* a_class, UObject* a_outer, const wchar_t* a_name, bool a_exactClass = false)
	{
		return static_cast<T*>(StaticFindObject(a_class, a_outer, a_name, a_exactClass));
	}

	inline UObject* StaticFindObjectFast(UClass* a_class, UObject* a_outer, FName a_name, bool a_exactClass = false, EObjectFlags a_exclusiveFlags = EObjectFlags::NoFlags, EInternalObjectFlags a_exclusiveInternalFlags = EInternalObjectFlags::None)
	{
		using func_t = UObject* (*)(UClass*, UObject*, FName, bool, EObjectFlags, EInternalObjectFlags);
		static REL::Relocation<func_t> func{ ID::StaticFindObjectFast };
		return func(a_class, a_outer, a_name, a_exactClass, a_exclusiveFlags, a_exclusiveInternalFlags);
	}

	template <class T>
	inline T* StaticFindObjectFast(UClass* a_class, UObject* a_outer, FName a_name, bool a_exactClass = false, EObjectFlags a_exclusiveFlags = EObjectFlags::NoFlags, EInternalObjectFlags a_exclusiveInternalFlags = EInternalObjectFlags::None)
	{
		return static_cast<T*>(StaticFindObjectFast(a_class, a_outer, a_name, a_exactClass, a_exclusiveFlags, a_exclusiveInternalFlags));
	}

	inline UObject* StaticFindObjectFastSafe(UClass* a_class, UObject* a_outer, FName a_name, bool a_exactClass = false, EObjectFlags a_exclusiveFlags = EObjectFlags::NoFlags, EInternalObjectFlags a_exclusiveInternalFlags = EInternalObjectFlags::None)
	{
		using func_t = UObject* (*)(UClass*, UObject*, FName, bool, EObjectFlags, EInternalObjectFlags);
		static REL::Relocation<func_t> func{ ID::StaticFindObjectFastSafe };
		return func(a_class, a_outer, a_name, a_exactClass, a_exclusiveFlags, a_exclusiveInternalFlags);
	}

	template <class T>
	inline T* StaticFindObjectFastSafe(UClass* a_class, UObject* a_outer, FName a_name, bool a_exactClass = false, EObjectFlags a_exclusiveFlags = EObjectFlags::NoFlags, EInternalObjectFlags a_exclusiveInternalFlags = EInternalObjectFlags::None)
	{
		return static_cast<T*>(StaticFindObjectFastSafe(a_class, a_outer, a_name, a_exactClass, a_exclusiveFlags, a_exclusiveInternalFlags));
	}

	inline UObject* StaticFindObjectSafe(UClass* a_class, UObject* a_outer, const wchar_t* a_name, bool a_exactClass = false)
	{
		using func_t = UObject* (*)(UClass*, UObject*, const wchar_t*, bool);
		static REL::Relocation<func_t> func{ ID::StaticFindObjectSafe };
		return func(a_class, a_outer, a_name, a_exactClass);
	}

	template <class T>
	inline T* StaticFindObjectSafe(UClass* a_class, UObject* a_outer, const wchar_t* a_name, bool a_exactClass = false)
	{
		return static_cast<T*>(StaticFindObjectSafe(a_class, a_outer, a_name, a_exactClass));
	}

	template <class T>
	inline T* FindObject(UObject* a_outer, const wchar_t* a_name, bool a_exactClass = false)
	{
		return StaticFindObject<T>(FindClass<T>(), a_outer, a_name, a_exactClass);
	}

	template <class T>
	inline T* FindObject(const wchar_t* a_name, bool a_exactClass = false)
	{
		return StaticFindObject<T>(FindClass<T>(), nullptr, a_name, a_exactClass);
	}

	template <class T>
	inline T* FindObjectFast(UObject* a_outer, FName a_name, bool a_exactClass = false, EObjectFlags a_exclusiveFlags = EObjectFlags::NoFlags)
	{
		return StaticFindObjectFast<T>(FindClass<T>(), a_outer, a_name, a_exactClass, a_exclusiveFlags);
	}

	template <class T>
	inline T* FindObjectFastSafe(UObject* a_outer, FName a_name, bool a_exactClass = false, EObjectFlags a_exclusiveFlags = EObjectFlags::NoFlags, EInternalObjectFlags a_exclusiveInternalFlags = EInternalObjectFlags::None)
	{
		return StaticFindObjectFastSafe<T>(FindClassSafe<T>(), a_outer, a_name, a_exactClass, a_exclusiveFlags, a_exclusiveInternalFlags);
	}

	template <class T>
	inline T* FindObjectSafe(UObject* a_outer, const wchar_t* a_name, bool a_exactClass = false)
	{
		return StaticFindObjectSafe<T>(FindClassSafe<T>(), a_outer, a_name, a_exactClass);
	}

	template <class T>
	inline T* FindObjectSafe(const wchar_t* a_name, bool a_exactClass = false)
	{
		return StaticFindObjectSafe<T>(FindClassSafe<T>(), nullptr, a_name, a_exactClass);
	}

	template <class T>
	UClass* FindClass()
	{
		static UClass* ptr{ nullptr };
		if (!ptr)
			ptr = StaticFindObject<UClass>(nullptr, nullptr, T::CLASS_PATH);

		return ptr;
	}

	template <class T>
	UClass* FindClassSafe()
	{
		static UClass* ptr{ nullptr };
		if (!ptr)
			ptr = StaticFindObjectSafe<UClass>(nullptr, nullptr, T::CLASS_PATH);

		return ptr;
	}

	template <class T>
	T* NewObject(UObject* a_outer, const UClass* a_class, FName a_name = EName::None, EObjectFlags a_flags = EObjectFlags::NoFlags, UObject* a_template = nullptr, bool a_copyTransientsFromClassDefaults = false, FObjectInstancingGraph* a_instanceGraph = nullptr, UPackage* a_externalPackage = nullptr)
	{
		FStaticConstructObjectParameters params(a_class);
		params.outer = a_outer;
		params.name = a_name;
		params.setFlags = a_flags;
		params.objectTemplate = a_template;
		params.copyTransientsFromClassDefaults = a_copyTransientsFromClassDefaults;
		params.instanceGraph = a_instanceGraph;
		params.externalPackage = a_externalPackage;
		return static_cast<T*>(StaticConstructObject_Internal(params));
	}

	template <class T>
	T* NewObject(UObject* a_outer, FName a_name = EName::None, EObjectFlags a_flags = EObjectFlags::NoFlags, UObject* a_template = nullptr, bool a_copyTransientsFromClassDefaults = false, FObjectInstancingGraph* a_instanceGraph = nullptr)
	{
		FStaticConstructObjectParameters params(FindClass<T>());
		params.outer = a_outer;
		params.name = a_name;
		params.setFlags = a_flags;
		params.objectTemplate = a_template;
		params.copyTransientsFromClassDefaults = a_copyTransientsFromClassDefaults;
		params.instanceGraph = a_instanceGraph;
		return static_cast<T*>(StaticConstructObject_Internal(params));
	}

	template <class T>
	T* NewObject(UObject* a_outer = (UObject*)GetTransientPackage())
	{
		FStaticConstructObjectParameters params(FindClass<T>());
		params.outer = a_outer;
		return static_cast<T*>(StaticConstructObject_Internal(params));
	}
}
