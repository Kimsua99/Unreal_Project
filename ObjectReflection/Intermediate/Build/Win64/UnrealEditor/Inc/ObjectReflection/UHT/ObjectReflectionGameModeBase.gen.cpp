// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ObjectReflection/ObjectReflectionGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeObjectReflectionGameModeBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	OBJECTREFLECTION_API UClass* Z_Construct_UClass_AObjectReflectionGameModeBase();
	OBJECTREFLECTION_API UClass* Z_Construct_UClass_AObjectReflectionGameModeBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_ObjectReflection();
// End Cross Module References
	void AObjectReflectionGameModeBase::StaticRegisterNativesAObjectReflectionGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AObjectReflectionGameModeBase);
	UClass* Z_Construct_UClass_AObjectReflectionGameModeBase_NoRegister()
	{
		return AObjectReflectionGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_AObjectReflectionGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AObjectReflectionGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_ObjectReflection,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AObjectReflectionGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "ObjectReflectionGameModeBase.h" },
		{ "ModuleRelativePath", "ObjectReflectionGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AObjectReflectionGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AObjectReflectionGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AObjectReflectionGameModeBase_Statics::ClassParams = {
		&AObjectReflectionGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AObjectReflectionGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AObjectReflectionGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AObjectReflectionGameModeBase()
	{
		if (!Z_Registration_Info_UClass_AObjectReflectionGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AObjectReflectionGameModeBase.OuterSingleton, Z_Construct_UClass_AObjectReflectionGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AObjectReflectionGameModeBase.OuterSingleton;
	}
	template<> OBJECTREFLECTION_API UClass* StaticClass<AObjectReflectionGameModeBase>()
	{
		return AObjectReflectionGameModeBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AObjectReflectionGameModeBase);
	AObjectReflectionGameModeBase::~AObjectReflectionGameModeBase() {}
	struct Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_ObjectReflection_Source_ObjectReflection_ObjectReflectionGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_ObjectReflection_Source_ObjectReflection_ObjectReflectionGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AObjectReflectionGameModeBase, AObjectReflectionGameModeBase::StaticClass, TEXT("AObjectReflectionGameModeBase"), &Z_Registration_Info_UClass_AObjectReflectionGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AObjectReflectionGameModeBase), 2541882832U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_ObjectReflection_Source_ObjectReflection_ObjectReflectionGameModeBase_h_3171902779(TEXT("/Script/ObjectReflection"),
		Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_ObjectReflection_Source_ObjectReflection_ObjectReflectionGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_ObjectReflection_Source_ObjectReflection_ObjectReflectionGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
