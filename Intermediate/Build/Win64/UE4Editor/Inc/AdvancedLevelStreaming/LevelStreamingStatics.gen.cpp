// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AdvancedLevelStreaming/Public/LevelStreamingStatics.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLevelStreamingStatics() {}
// Cross Module References
	ADVANCEDLEVELSTREAMING_API UClass* Z_Construct_UClass_ULevelStreamingStatics_NoRegister();
	ADVANCEDLEVELSTREAMING_API UClass* Z_Construct_UClass_ULevelStreamingStatics();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_AdvancedLevelStreaming();
	ADVANCEDLEVELSTREAMING_API UFunction* Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FTransform();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FLatentActionInfo();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
// End Cross Module References
	void ULevelStreamingStatics::StaticRegisterNativesULevelStreamingStatics()
	{
		UClass* Class = ULevelStreamingStatics::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "LoadStreamLevelWithTransform", &ULevelStreamingStatics::execLoadStreamLevelWithTransform },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics
	{
		struct LevelStreamingStatics_eventLoadStreamLevelWithTransform_Parms
		{
			const UObject* WorldContextObject;
			FName LevelName;
			bool bMakeVisibleAfterLoad;
			bool bShouldBlockOnLoad;
			FLatentActionInfo LatentInfo;
			FTransform LevelTransform;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_LevelTransform;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_LatentInfo;
		static void NewProp_bShouldBlockOnLoad_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bShouldBlockOnLoad;
		static void NewProp_bMakeVisibleAfterLoad_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bMakeVisibleAfterLoad;
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_LevelName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WorldContextObject_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_LevelTransform = { UE4CodeGen_Private::EPropertyClass::Struct, "LevelTransform", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(LevelStreamingStatics_eventLoadStreamLevelWithTransform_Parms, LevelTransform), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_LatentInfo = { UE4CodeGen_Private::EPropertyClass::Struct, "LatentInfo", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(LevelStreamingStatics_eventLoadStreamLevelWithTransform_Parms, LatentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_bShouldBlockOnLoad_SetBit(void* Obj)
	{
		((LevelStreamingStatics_eventLoadStreamLevelWithTransform_Parms*)Obj)->bShouldBlockOnLoad = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_bShouldBlockOnLoad = { UE4CodeGen_Private::EPropertyClass::Bool, "bShouldBlockOnLoad", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(LevelStreamingStatics_eventLoadStreamLevelWithTransform_Parms), &Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_bShouldBlockOnLoad_SetBit, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_bMakeVisibleAfterLoad_SetBit(void* Obj)
	{
		((LevelStreamingStatics_eventLoadStreamLevelWithTransform_Parms*)Obj)->bMakeVisibleAfterLoad = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_bMakeVisibleAfterLoad = { UE4CodeGen_Private::EPropertyClass::Bool, "bMakeVisibleAfterLoad", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(LevelStreamingStatics_eventLoadStreamLevelWithTransform_Parms), &Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_bMakeVisibleAfterLoad_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_LevelName = { UE4CodeGen_Private::EPropertyClass::Name, "LevelName", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(LevelStreamingStatics_eventLoadStreamLevelWithTransform_Parms, LevelName), METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_WorldContextObject_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_WorldContextObject = { UE4CodeGen_Private::EPropertyClass::Object, "WorldContextObject", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000082, 1, nullptr, STRUCT_OFFSET(LevelStreamingStatics_eventLoadStreamLevelWithTransform_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_WorldContextObject_MetaData, ARRAY_COUNT(Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_WorldContextObject_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_LevelTransform,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_LatentInfo,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_bShouldBlockOnLoad,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_bMakeVisibleAfterLoad,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_LevelName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::NewProp_WorldContextObject,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::Function_MetaDataParams[] = {
		{ "Category", "Game" },
		{ "Latent", "" },
		{ "LatentInfo", "LatentInfo" },
		{ "ModuleRelativePath", "Public/LevelStreamingStatics.h" },
		{ "WorldContext", "WorldContextObject" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULevelStreamingStatics, "LoadStreamLevelWithTransform", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04822401, sizeof(LevelStreamingStatics_eventLoadStreamLevelWithTransform_Parms), Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::PropPointers), 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ULevelStreamingStatics_NoRegister()
	{
		return ULevelStreamingStatics::StaticClass();
	}
	struct Z_Construct_UClass_ULevelStreamingStatics_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULevelStreamingStatics_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_AdvancedLevelStreaming,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULevelStreamingStatics_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULevelStreamingStatics_LoadStreamLevelWithTransform, "LoadStreamLevelWithTransform" }, // 441805999
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULevelStreamingStatics_Statics::Class_MetaDataParams[] = {
		{ "DisplayName", "LevelStreamingStatics" },
		{ "IncludePath", "LevelStreamingStatics.h" },
		{ "ModuleRelativePath", "Public/LevelStreamingStatics.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULevelStreamingStatics_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULevelStreamingStatics>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULevelStreamingStatics_Statics::ClassParams = {
		&ULevelStreamingStatics::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x001000A0u,
		FuncInfo, ARRAY_COUNT(FuncInfo),
		nullptr, 0,
		"AdvancedLevelStreaming",
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_ULevelStreamingStatics_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ULevelStreamingStatics_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULevelStreamingStatics()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULevelStreamingStatics_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULevelStreamingStatics, 4038567549);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULevelStreamingStatics(Z_Construct_UClass_ULevelStreamingStatics, &ULevelStreamingStatics::StaticClass, TEXT("/Script/AdvancedLevelStreaming"), TEXT("ULevelStreamingStatics"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULevelStreamingStatics);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
