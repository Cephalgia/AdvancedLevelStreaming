// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AdvancedLevelStreaming/Public/LevelManager.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLevelManager() {}
// Cross Module References
	ADVANCEDLEVELSTREAMING_API UScriptStruct* Z_Construct_UScriptStruct_FLevelInfo();
	UPackage* Z_Construct_UPackage__Script_AdvancedLevelStreaming();
	ENGINE_API UClass* Z_Construct_UClass_ULevelStreaming_NoRegister();
	ADVANCEDLEVELSTREAMING_API UClass* Z_Construct_UClass_ULevelManager_NoRegister();
	ADVANCEDLEVELSTREAMING_API UClass* Z_Construct_UClass_ULevelManager();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
// End Cross Module References
class UScriptStruct* FLevelInfo::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ADVANCEDLEVELSTREAMING_API uint32 Get_Z_Construct_UScriptStruct_FLevelInfo_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLevelInfo, Z_Construct_UPackage__Script_AdvancedLevelStreaming(), TEXT("LevelInfo"), sizeof(FLevelInfo), Get_Z_Construct_UScriptStruct_FLevelInfo_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLevelInfo(FLevelInfo::StaticStruct, TEXT("/Script/AdvancedLevelStreaming"), TEXT("LevelInfo"), false, nullptr, nullptr);
static struct FScriptStruct_AdvancedLevelStreaming_StaticRegisterNativesFLevelInfo
{
	FScriptStruct_AdvancedLevelStreaming_StaticRegisterNativesFLevelInfo()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LevelInfo")),new UScriptStruct::TCppStructOps<FLevelInfo>);
	}
} ScriptStruct_AdvancedLevelStreaming_StaticRegisterNativesFLevelInfo;
	struct Z_Construct_UScriptStruct_FLevelInfo_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LevelStreaming_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_LevelStreaming;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLevelInfo_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LevelManager.h" },
		{ "ToolTip", "class ALevelStreamingDoorPoint;\nclass ALevelStreamingTrigger;" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLevelInfo_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLevelInfo>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLevelInfo_Statics::NewProp_LevelStreaming_MetaData[] = {
		{ "ModuleRelativePath", "Public/LevelManager.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FLevelInfo_Statics::NewProp_LevelStreaming = { UE4CodeGen_Private::EPropertyClass::Object, "LevelStreaming", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000000, 1, nullptr, STRUCT_OFFSET(FLevelInfo, LevelStreaming), Z_Construct_UClass_ULevelStreaming_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FLevelInfo_Statics::NewProp_LevelStreaming_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FLevelInfo_Statics::NewProp_LevelStreaming_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLevelInfo_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLevelInfo_Statics::NewProp_LevelStreaming,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLevelInfo_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AdvancedLevelStreaming,
		nullptr,
		&NewStructOps,
		"LevelInfo",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		sizeof(FLevelInfo),
		alignof(FLevelInfo),
		Z_Construct_UScriptStruct_FLevelInfo_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FLevelInfo_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLevelInfo_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FLevelInfo_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLevelInfo()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLevelInfo_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AdvancedLevelStreaming();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LevelInfo"), sizeof(FLevelInfo), Get_Z_Construct_UScriptStruct_FLevelInfo_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLevelInfo_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLevelInfo_CRC() { return 3801417067U; }
	void ULevelManager::StaticRegisterNativesULevelManager()
	{
	}
	UClass* Z_Construct_UClass_ULevelManager_NoRegister()
	{
		return ULevelManager::StaticClass();
	}
	struct Z_Construct_UClass_ULevelManager_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULevelManager_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_AdvancedLevelStreaming,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULevelManager_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "DisplayName", "LevelManager" },
		{ "IncludePath", "LevelManager.h" },
		{ "ModuleRelativePath", "Public/LevelManager.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULevelManager_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULevelManager>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULevelManager_Statics::ClassParams = {
		&ULevelManager::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x001000A0u,
		nullptr, 0,
		nullptr, 0,
		"AdvancedLevelStreaming",
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_ULevelManager_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ULevelManager_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULevelManager()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULevelManager_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULevelManager, 3874305967);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULevelManager(Z_Construct_UClass_ULevelManager, &ULevelManager::StaticClass, TEXT("/Script/AdvancedLevelStreaming"), TEXT("ULevelManager"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULevelManager);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
