#pragma once

#define UE_DEFINE_CLASS(a_class, a_packageName, a_objectName)     \
	using CLASS = a_class;                                        \
	static constexpr auto CLASS_PACKAGE_NAME{ L##a_packageName }; \
	static constexpr auto CLASS_OBJECT_NAME{ L##a_objectName };   \
	static constexpr auto CLASS_PATH{ L"/Script/" L##a_packageName L"." L##a_objectName };

#define UE_DEFINE_CLASS_INTRINSIC(a_class, a_packageName, a_objectName, a_flags, a_castFlags) \
	UE_DEFINE_CLASS(a_class, a_packageName, a_objectName)                                     \
	static constexpr auto CLASS_FLAGS{ a_flags };                                             \
	static constexpr auto CLASS_CAST_FLAGS{ a_castFlags };
 
#define UE_DEFINE_UOBJECT(a_class, a_super, a_packageName, a_objectName) \
	using CLASS_SUPER = a_super;                                         \
	UE_DEFINE_CLASS(a_class, a_packageName, a_objectName)

#define UE_DEFINE_UOBJECT_INTRINSIC(a_class, a_super, a_packageName, a_objectName, a_flags, a_castFlags) \
	using CLASS_SUPER = a_super;                                                                         \
	UE_DEFINE_CLASS_INTRINSIC(a_class, a_packageName, a_objectName, a_flags, a_castFlags)

#define UE_DEFINE_IINTERFACE(a_class, a_packageName, a_objectName) \
	using CLASS_TYPE = UInterface;                                 \
	UE_DEFINE_CLASS(a_class, a_packageName, a_objectName)
	
