// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AdvancedLevelStreaming/Public/LevelStreamingDoorPoint.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLevelStreamingDoorPoint() {}
// Cross Module References
	ADVANCEDLEVELSTREAMING_API UClass* Z_Construct_UClass_ALevelStreamingDoorPoint_NoRegister();
	ADVANCEDLEVELSTREAMING_API UClass* Z_Construct_UClass_ALevelStreamingDoorPoint();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_AdvancedLevelStreaming();
	ENGINE_API UClass* Z_Construct_UClass_UArrowComponent_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FTransform();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
// End Cross Module References
	void ALevelStreamingDoorPoint::StaticRegisterNativesALevelStreamingDoorPoint()
	{
	}
	UClass* Z_Construct_UClass_ALevelStreamingDoorPoint_NoRegister()
	{
		return ALevelStreamingDoorPoint::StaticClass();
	}
	struct Z_Construct_UClass_ALevelStreamingDoorPoint_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LevelStreamingComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_LevelStreamingComponent;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LevelStreamingPointRelative_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_LevelStreamingPointRelative;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DoorStaticMesh_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_DoorStaticMesh;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_AdvancedLevelStreaming,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "DisplayName", "LevelStreamingDoorPoint" },
		{ "IncludePath", "LevelStreamingDoorPoint.h" },
		{ "ModuleRelativePath", "Public/LevelStreamingDoorPoint.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::NewProp_LevelStreamingComponent_MetaData[] = {
		{ "Category", "LevelTransform" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/LevelStreamingDoorPoint.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::NewProp_LevelStreamingComponent = { UE4CodeGen_Private::EPropertyClass::Object, "LevelStreamingComponent", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x00100000000a0009, 1, nullptr, STRUCT_OFFSET(ALevelStreamingDoorPoint, LevelStreamingComponent), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::NewProp_LevelStreamingComponent_MetaData, ARRAY_COUNT(Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::NewProp_LevelStreamingComponent_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::NewProp_LevelStreamingPointRelative_MetaData[] = {
		{ "Category", "LevelStreaming" },
		{ "ModuleRelativePath", "Public/LevelStreamingDoorPoint.h" },
		{ "ToolTip", "Door component (closing and opening)" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::NewProp_LevelStreamingPointRelative = { UE4CodeGen_Private::EPropertyClass::Struct, "LevelStreamingPointRelative", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000001, 1, nullptr, STRUCT_OFFSET(ALevelStreamingDoorPoint, LevelStreamingPointRelative), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::NewProp_LevelStreamingPointRelative_MetaData, ARRAY_COUNT(Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::NewProp_LevelStreamingPointRelative_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::NewProp_DoorStaticMesh_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/LevelStreamingDoorPoint.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::NewProp_DoorStaticMesh = { UE4CodeGen_Private::EPropertyClass::Object, "DoorStaticMesh", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000080008, 1, nullptr, STRUCT_OFFSET(ALevelStreamingDoorPoint, DoorStaticMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::NewProp_DoorStaticMesh_MetaData, ARRAY_COUNT(Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::NewProp_DoorStaticMesh_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::NewProp_LevelStreamingComponent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::NewProp_LevelStreamingPointRelative,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::NewProp_DoorStaticMesh,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALevelStreamingDoorPoint>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::ClassParams = {
		&ALevelStreamingDoorPoint::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x009000A0u,
		nullptr, 0,
		Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::PropPointers),
		"AdvancedLevelStreaming",
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ALevelStreamingDoorPoint()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ALevelStreamingDoorPoint_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ALevelStreamingDoorPoint, 1763583851);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ALevelStreamingDoorPoint(Z_Construct_UClass_ALevelStreamingDoorPoint, &ALevelStreamingDoorPoint::StaticClass, TEXT("/Script/AdvancedLevelStreaming"), TEXT("ALevelStreamingDoorPoint"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALevelStreamingDoorPoint);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
