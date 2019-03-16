// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AdvancedLevelStreaming/Public/LevelStreamingTrigger.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLevelStreamingTrigger() {}
// Cross Module References
	ADVANCEDLEVELSTREAMING_API UClass* Z_Construct_UClass_ALevelStreamingTrigger_NoRegister();
	ADVANCEDLEVELSTREAMING_API UClass* Z_Construct_UClass_ALevelStreamingTrigger();
	ENGINE_API UClass* Z_Construct_UClass_ATriggerVolume();
	UPackage* Z_Construct_UPackage__Script_AdvancedLevelStreaming();
	ADVANCEDLEVELSTREAMING_API UFunction* Z_Construct_UFunction_ALevelStreamingTrigger_OnBeginOverlap();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	ADVANCEDLEVELSTREAMING_API UFunction* Z_Construct_UFunction_ALevelStreamingTrigger_OnEndOverlap();
// End Cross Module References
	void ALevelStreamingTrigger::StaticRegisterNativesALevelStreamingTrigger()
	{
		UClass* Class = ALevelStreamingTrigger::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnBeginOverlap", &ALevelStreamingTrigger::execOnBeginOverlap },
			{ "OnEndOverlap", &ALevelStreamingTrigger::execOnEndOverlap },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ALevelStreamingTrigger_OnBeginOverlap_Statics
	{
		struct LevelStreamingTrigger_eventOnBeginOverlap_Parms
		{
			AActor* OverlappingActor;
			AActor* OtherActor;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OverlappingActor;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ALevelStreamingTrigger_OnBeginOverlap_Statics::NewProp_OtherActor = { UE4CodeGen_Private::EPropertyClass::Object, "OtherActor", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(LevelStreamingTrigger_eventOnBeginOverlap_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ALevelStreamingTrigger_OnBeginOverlap_Statics::NewProp_OverlappingActor = { UE4CodeGen_Private::EPropertyClass::Object, "OverlappingActor", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(LevelStreamingTrigger_eventOnBeginOverlap_Parms, OverlappingActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ALevelStreamingTrigger_OnBeginOverlap_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALevelStreamingTrigger_OnBeginOverlap_Statics::NewProp_OtherActor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALevelStreamingTrigger_OnBeginOverlap_Statics::NewProp_OverlappingActor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ALevelStreamingTrigger_OnBeginOverlap_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LevelStreamingTrigger.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ALevelStreamingTrigger_OnBeginOverlap_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ALevelStreamingTrigger, "OnBeginOverlap", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00020401, sizeof(LevelStreamingTrigger_eventOnBeginOverlap_Parms), Z_Construct_UFunction_ALevelStreamingTrigger_OnBeginOverlap_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_ALevelStreamingTrigger_OnBeginOverlap_Statics::PropPointers), 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ALevelStreamingTrigger_OnBeginOverlap_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_ALevelStreamingTrigger_OnBeginOverlap_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ALevelStreamingTrigger_OnBeginOverlap()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ALevelStreamingTrigger_OnBeginOverlap_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ALevelStreamingTrigger_OnEndOverlap_Statics
	{
		struct LevelStreamingTrigger_eventOnEndOverlap_Parms
		{
			AActor* OverlappingActor;
			AActor* OtherActor;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OverlappingActor;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ALevelStreamingTrigger_OnEndOverlap_Statics::NewProp_OtherActor = { UE4CodeGen_Private::EPropertyClass::Object, "OtherActor", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(LevelStreamingTrigger_eventOnEndOverlap_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ALevelStreamingTrigger_OnEndOverlap_Statics::NewProp_OverlappingActor = { UE4CodeGen_Private::EPropertyClass::Object, "OverlappingActor", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(LevelStreamingTrigger_eventOnEndOverlap_Parms, OverlappingActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ALevelStreamingTrigger_OnEndOverlap_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALevelStreamingTrigger_OnEndOverlap_Statics::NewProp_OtherActor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALevelStreamingTrigger_OnEndOverlap_Statics::NewProp_OverlappingActor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ALevelStreamingTrigger_OnEndOverlap_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LevelStreamingTrigger.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ALevelStreamingTrigger_OnEndOverlap_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ALevelStreamingTrigger, "OnEndOverlap", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00020401, sizeof(LevelStreamingTrigger_eventOnEndOverlap_Parms), Z_Construct_UFunction_ALevelStreamingTrigger_OnEndOverlap_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_ALevelStreamingTrigger_OnEndOverlap_Statics::PropPointers), 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ALevelStreamingTrigger_OnEndOverlap_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_ALevelStreamingTrigger_OnEndOverlap_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ALevelStreamingTrigger_OnEndOverlap()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ALevelStreamingTrigger_OnEndOverlap_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ALevelStreamingTrigger_NoRegister()
	{
		return ALevelStreamingTrigger::StaticClass();
	}
	struct Z_Construct_UClass_ALevelStreamingTrigger_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ALevelStreamingTrigger_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ATriggerVolume,
		(UObject* (*)())Z_Construct_UPackage__Script_AdvancedLevelStreaming,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ALevelStreamingTrigger_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ALevelStreamingTrigger_OnBeginOverlap, "OnBeginOverlap" }, // 2898600726
		{ &Z_Construct_UFunction_ALevelStreamingTrigger_OnEndOverlap, "OnEndOverlap" }, // 655075566
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ALevelStreamingTrigger_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "DisplayName", "LevelStreamingTrigger" },
		{ "HideCategories", "Brush Physics Object Display Rendering Physics Input Blueprint" },
		{ "IncludePath", "LevelStreamingTrigger.h" },
		{ "ModuleRelativePath", "Public/LevelStreamingTrigger.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ALevelStreamingTrigger_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALevelStreamingTrigger>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ALevelStreamingTrigger_Statics::ClassParams = {
		&ALevelStreamingTrigger::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x009000A0u,
		FuncInfo, ARRAY_COUNT(FuncInfo),
		nullptr, 0,
		"AdvancedLevelStreaming",
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_ALevelStreamingTrigger_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ALevelStreamingTrigger_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ALevelStreamingTrigger()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ALevelStreamingTrigger_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ALevelStreamingTrigger, 3711235942);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ALevelStreamingTrigger(Z_Construct_UClass_ALevelStreamingTrigger, &ALevelStreamingTrigger::StaticClass, TEXT("/Script/AdvancedLevelStreaming"), TEXT("ALevelStreamingTrigger"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALevelStreamingTrigger);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
