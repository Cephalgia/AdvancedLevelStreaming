// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
#ifdef ADVANCEDLEVELSTREAMING_LevelStreamingTrigger_generated_h
#error "LevelStreamingTrigger.generated.h already included, missing '#pragma once' in LevelStreamingTrigger.h"
#endif
#define ADVANCEDLEVELSTREAMING_LevelStreamingTrigger_generated_h

#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h_10_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnEndOverlap) \
	{ \
		P_GET_OBJECT(AActor,Z_Param_OverlappingActor); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnEndOverlap(Z_Param_OverlappingActor,Z_Param_OtherActor); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execOnBeginOverlap) \
	{ \
		P_GET_OBJECT(AActor,Z_Param_OverlappingActor); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnBeginOverlap(Z_Param_OverlappingActor,Z_Param_OtherActor); \
		P_NATIVE_END; \
	}


#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnEndOverlap) \
	{ \
		P_GET_OBJECT(AActor,Z_Param_OverlappingActor); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnEndOverlap(Z_Param_OverlappingActor,Z_Param_OtherActor); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execOnBeginOverlap) \
	{ \
		P_GET_OBJECT(AActor,Z_Param_OverlappingActor); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnBeginOverlap(Z_Param_OverlappingActor,Z_Param_OtherActor); \
		P_NATIVE_END; \
	}


#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h_10_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesALevelStreamingTrigger(); \
	friend struct Z_Construct_UClass_ALevelStreamingTrigger_Statics; \
public: \
	DECLARE_CLASS(ALevelStreamingTrigger, ATriggerVolume, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AdvancedLevelStreaming"), NO_API) \
	DECLARE_SERIALIZER(ALevelStreamingTrigger) \
	static const TCHAR* StaticConfigName() {return TEXT("AdvancedLevelStreaming");} \



#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h_10_INCLASS \
private: \
	static void StaticRegisterNativesALevelStreamingTrigger(); \
	friend struct Z_Construct_UClass_ALevelStreamingTrigger_Statics; \
public: \
	DECLARE_CLASS(ALevelStreamingTrigger, ATriggerVolume, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AdvancedLevelStreaming"), NO_API) \
	DECLARE_SERIALIZER(ALevelStreamingTrigger) \
	static const TCHAR* StaticConfigName() {return TEXT("AdvancedLevelStreaming");} \



#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h_10_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ALevelStreamingTrigger(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ALevelStreamingTrigger) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ALevelStreamingTrigger); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ALevelStreamingTrigger); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ALevelStreamingTrigger(ALevelStreamingTrigger&&); \
	NO_API ALevelStreamingTrigger(const ALevelStreamingTrigger&); \
public:


#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h_10_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ALevelStreamingTrigger(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ALevelStreamingTrigger(ALevelStreamingTrigger&&); \
	NO_API ALevelStreamingTrigger(const ALevelStreamingTrigger&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ALevelStreamingTrigger); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ALevelStreamingTrigger); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ALevelStreamingTrigger)


#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h_10_PRIVATE_PROPERTY_OFFSET
#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h_7_PROLOG
#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h_10_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h_10_PRIVATE_PROPERTY_OFFSET \
	Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h_10_RPC_WRAPPERS \
	Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h_10_INCLASS \
	Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h_10_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h_10_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h_10_PRIVATE_PROPERTY_OFFSET \
	Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h_10_INCLASS_NO_PURE_DECLS \
	Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h_10_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class LevelStreamingTrigger."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Engine_Plugins_AdvancedLevelStreaming_Source_AdvancedLevelStreaming_Public_LevelStreamingTrigger_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
