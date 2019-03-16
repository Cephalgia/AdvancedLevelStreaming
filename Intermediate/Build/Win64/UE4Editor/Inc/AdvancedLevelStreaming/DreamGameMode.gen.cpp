// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AdvancedLevelStreaming/Public/DreamGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDreamGameMode() {}
// Cross Module References
	ADVANCEDLEVELSTREAMING_API UClass* Z_Construct_UClass_ADreamGameMode_NoRegister();
	ADVANCEDLEVELSTREAMING_API UClass* Z_Construct_UClass_ADreamGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_AdvancedLevelStreaming();
	ADVANCEDLEVELSTREAMING_API UClass* Z_Construct_UClass_ULevelManager_NoRegister();
// End Cross Module References
	void ADreamGameMode::StaticRegisterNativesADreamGameMode()
	{
	}
	UClass* Z_Construct_UClass_ADreamGameMode_NoRegister()
	{
		return ADreamGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ADreamGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LevelManager_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_LevelManager;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADreamGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_AdvancedLevelStreaming,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADreamGameMode_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "DisplayName", "DreamGameMode" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "DreamGameMode.h" },
		{ "ModuleRelativePath", "Public/DreamGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADreamGameMode_Statics::NewProp_LevelManager_MetaData[] = {
		{ "ModuleRelativePath", "Public/DreamGameMode.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ADreamGameMode_Statics::NewProp_LevelManager = { UE4CodeGen_Private::EPropertyClass::Object, "LevelManager", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000000, 1, nullptr, STRUCT_OFFSET(ADreamGameMode, LevelManager), Z_Construct_UClass_ULevelManager_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ADreamGameMode_Statics::NewProp_LevelManager_MetaData, ARRAY_COUNT(Z_Construct_UClass_ADreamGameMode_Statics::NewProp_LevelManager_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADreamGameMode_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADreamGameMode_Statics::NewProp_LevelManager,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADreamGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADreamGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADreamGameMode_Statics::ClassParams = {
		&ADreamGameMode::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x009002A8u,
		nullptr, 0,
		Z_Construct_UClass_ADreamGameMode_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UClass_ADreamGameMode_Statics::PropPointers),
		"AdvancedLevelStreaming",
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_ADreamGameMode_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ADreamGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADreamGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADreamGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADreamGameMode, 975402057);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADreamGameMode(Z_Construct_UClass_ADreamGameMode, &ADreamGameMode::StaticClass, TEXT("/Script/AdvancedLevelStreaming"), TEXT("ADreamGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADreamGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
