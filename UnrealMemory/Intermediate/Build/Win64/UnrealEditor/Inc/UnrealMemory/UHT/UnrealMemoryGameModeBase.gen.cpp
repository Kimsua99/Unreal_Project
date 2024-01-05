// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UnrealMemory/UnrealMemoryGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUnrealMemoryGameModeBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UNREALMEMORY_API UClass* Z_Construct_UClass_AUnrealMemoryGameModeBase();
	UNREALMEMORY_API UClass* Z_Construct_UClass_AUnrealMemoryGameModeBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_UnrealMemory();
// End Cross Module References
	void AUnrealMemoryGameModeBase::StaticRegisterNativesAUnrealMemoryGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AUnrealMemoryGameModeBase);
	UClass* Z_Construct_UClass_AUnrealMemoryGameModeBase_NoRegister()
	{
		return AUnrealMemoryGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_AUnrealMemoryGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AUnrealMemoryGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_UnrealMemory,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AUnrealMemoryGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "UnrealMemoryGameModeBase.h" },
		{ "ModuleRelativePath", "UnrealMemoryGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AUnrealMemoryGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AUnrealMemoryGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AUnrealMemoryGameModeBase_Statics::ClassParams = {
		&AUnrealMemoryGameModeBase::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_AUnrealMemoryGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AUnrealMemoryGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AUnrealMemoryGameModeBase()
	{
		if (!Z_Registration_Info_UClass_AUnrealMemoryGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AUnrealMemoryGameModeBase.OuterSingleton, Z_Construct_UClass_AUnrealMemoryGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AUnrealMemoryGameModeBase.OuterSingleton;
	}
	template<> UNREALMEMORY_API UClass* StaticClass<AUnrealMemoryGameModeBase>()
	{
		return AUnrealMemoryGameModeBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AUnrealMemoryGameModeBase);
	AUnrealMemoryGameModeBase::~AUnrealMemoryGameModeBase() {}
	struct Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealMemory_Source_UnrealMemory_UnrealMemoryGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealMemory_Source_UnrealMemory_UnrealMemoryGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AUnrealMemoryGameModeBase, AUnrealMemoryGameModeBase::StaticClass, TEXT("AUnrealMemoryGameModeBase"), &Z_Registration_Info_UClass_AUnrealMemoryGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AUnrealMemoryGameModeBase), 1234158329U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealMemory_Source_UnrealMemory_UnrealMemoryGameModeBase_h_2400739800(TEXT("/Script/UnrealMemory"),
		Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealMemory_Source_UnrealMemory_UnrealMemoryGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealMemory_Source_UnrealMemory_UnrealMemoryGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
