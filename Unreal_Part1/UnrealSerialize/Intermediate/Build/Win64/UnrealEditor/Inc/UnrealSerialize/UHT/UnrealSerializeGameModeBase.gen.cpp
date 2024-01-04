// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UnrealSerialize/UnrealSerializeGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUnrealSerializeGameModeBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UNREALSERIALIZE_API UClass* Z_Construct_UClass_AUnrealSerializeGameModeBase();
	UNREALSERIALIZE_API UClass* Z_Construct_UClass_AUnrealSerializeGameModeBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_UnrealSerialize();
// End Cross Module References
	void AUnrealSerializeGameModeBase::StaticRegisterNativesAUnrealSerializeGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AUnrealSerializeGameModeBase);
	UClass* Z_Construct_UClass_AUnrealSerializeGameModeBase_NoRegister()
	{
		return AUnrealSerializeGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_AUnrealSerializeGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AUnrealSerializeGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_UnrealSerialize,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AUnrealSerializeGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "UnrealSerializeGameModeBase.h" },
		{ "ModuleRelativePath", "UnrealSerializeGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AUnrealSerializeGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AUnrealSerializeGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AUnrealSerializeGameModeBase_Statics::ClassParams = {
		&AUnrealSerializeGameModeBase::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_AUnrealSerializeGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AUnrealSerializeGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AUnrealSerializeGameModeBase()
	{
		if (!Z_Registration_Info_UClass_AUnrealSerializeGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AUnrealSerializeGameModeBase.OuterSingleton, Z_Construct_UClass_AUnrealSerializeGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AUnrealSerializeGameModeBase.OuterSingleton;
	}
	template<> UNREALSERIALIZE_API UClass* StaticClass<AUnrealSerializeGameModeBase>()
	{
		return AUnrealSerializeGameModeBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AUnrealSerializeGameModeBase);
	AUnrealSerializeGameModeBase::~AUnrealSerializeGameModeBase() {}
	struct Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealSerialize_Source_UnrealSerialize_UnrealSerializeGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealSerialize_Source_UnrealSerialize_UnrealSerializeGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AUnrealSerializeGameModeBase, AUnrealSerializeGameModeBase::StaticClass, TEXT("AUnrealSerializeGameModeBase"), &Z_Registration_Info_UClass_AUnrealSerializeGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AUnrealSerializeGameModeBase), 3282216291U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealSerialize_Source_UnrealSerialize_UnrealSerializeGameModeBase_h_1056579040(TEXT("/Script/UnrealSerialize"),
		Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealSerialize_Source_UnrealSerialize_UnrealSerializeGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealSerialize_Source_UnrealSerialize_UnrealSerializeGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
