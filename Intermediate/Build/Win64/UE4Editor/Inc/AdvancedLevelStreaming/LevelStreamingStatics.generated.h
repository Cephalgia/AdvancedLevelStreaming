// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
struct FLatentActionInfo;
struct FTransform;
#ifdef ADVANCEDLEVELSTREAMING_LevelStreamingStatics_generated_h
#error "LevelStreamingStatics.generated.h already included, missing '#pragma once' in LevelStreamingStatics.h"
#endif
#define ADVANCEDLEVELSTREAMING_LevelStreamingStatics_generated_h

#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h_10_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execLoadStreamLevelWithTransform) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject); \
		P_GET_PROPERTY(UNameProperty,Z_Param_LevelName); \
		P_GET_UBOOL(Z_Param_bMakeVisibleAfterLoad); \
		P_GET_UBOOL(Z_Param_bShouldBlockOnLoad); \
		P_GET_STRUCT(FLatentActionInfo,Z_Param_LatentInfo); \
		P_GET_STRUCT(FTransform,Z_Param_LevelTransform); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		ULevelStreamingStatics::LoadStreamLevelWithTransform(Z_Param_WorldContextObject,Z_Param_LevelName,Z_Param_bMakeVisibleAfterLoad,Z_Param_bShouldBlockOnLoad,Z_Param_LatentInfo,Z_Param_LevelTransform); \
		P_NATIVE_END; \
	}


#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execLoadStreamLevelWithTransform) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject); \
		P_GET_PROPERTY(UNameProperty,Z_Param_LevelName); \
		P_GET_UBOOL(Z_Param_bMakeVisibleAfterLoad); \
		P_GET_UBOOL(Z_Param_bShouldBlockOnLoad); \
		P_GET_STRUCT(FLatentActionInfo,Z_Param_LatentInfo); \
		P_GET_STRUCT(FTransform,Z_Param_LevelTransform); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		ULevelStreamingStatics::LoadStreamLevelWithTransform(Z_Param_WorldContextObject,Z_Param_LevelName,Z_Param_bMakeVisibleAfterLoad,Z_Param_bShouldBlockOnLoad,Z_Param_LatentInfo,Z_Param_LevelTransform); \
		P_NATIVE_END; \
	}


#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h_10_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULevelStreamingStatics(); \
	friend struct Z_Construct_UClass_ULevelStreamingStatics_Statics; \
public: \
	DECLARE_CLASS(ULevelStreamingStatics, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AdvancedLevelStreaming"), NO_API) \
	DECLARE_SERIALIZER(ULevelStreamingStatics) \
	static const TCHAR* StaticConfigName() {return TEXT("AdvancedLevelStreaming");} \



#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h_10_INCLASS \
private: \
	static void StaticRegisterNativesULevelStreamingStatics(); \
	friend struct Z_Construct_UClass_ULevelStreamingStatics_Statics; \
public: \
	DECLARE_CLASS(ULevelStreamingStatics, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AdvancedLevelStreaming"), NO_API) \
	DECLARE_SERIALIZER(ULevelStreamingStatics) \
	static const TCHAR* StaticConfigName() {return TEXT("AdvancedLevelStreaming");} \



#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h_10_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULevelStreamingStatics(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULevelStreamingStatics) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULevelStreamingStatics); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULevelStreamingStatics); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULevelStreamingStatics(ULevelStreamingStatics&&); \
	NO_API ULevelStreamingStatics(const ULevelStreamingStatics&); \
public:


#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h_10_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULevelStreamingStatics(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULevelStreamingStatics(ULevelStreamingStatics&&); \
	NO_API ULevelStreamingStatics(const ULevelStreamingStatics&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULevelStreamingStatics); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULevelStreamingStatics); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULevelStreamingStatics)


#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h_10_PRIVATE_PROPERTY_OFFSET
#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h_7_PROLOG
#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h_10_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h_10_PRIVATE_PROPERTY_OFFSET \
	Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h_10_RPC_WRAPPERS \
	Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h_10_INCLASS \
	Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h_10_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h_10_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h_10_PRIVATE_PROPERTY_OFFSET \
	Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h_10_INCLASS_NO_PURE_DECLS \
	Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h_10_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class LevelStreamingStatics."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingStatics_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
