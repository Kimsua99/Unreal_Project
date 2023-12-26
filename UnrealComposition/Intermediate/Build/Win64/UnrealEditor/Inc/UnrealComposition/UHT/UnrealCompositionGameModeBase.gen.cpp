// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UnrealComposition/UnrealCompositionGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUnrealCompositionGameModeBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UNREALCOMPOSITION_API UClass* Z_Construct_UClass_AUnrealCompositionGameModeBase();
	UNREALCOMPOSITION_API UClass* Z_Construct_UClass_AUnrealCompositionGameModeBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_UnrealComposition();
// End Cross Module References
	void AUnrealCompositionGameModeBase::StaticRegisterNativesAUnrealCompositionGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AUnrealCompositionGameModeBase);
	UClass* Z_Construct_UClass_AUnrealCompositionGameModeBase_NoRegister()
	{
		return AUnrealCompositionGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_AUnrealCompositionGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AUnrealCompositionGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_UnrealComposition,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AUnrealCompositionGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "UnrealCompositionGameModeBase.h" },
		{ "ModuleRelativePath", "UnrealCompositionGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AUnrealCompositionGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AUnrealCompositionGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AUnrealCompositionGameModeBase_Statics::ClassParams = {
		&AUnrealCompositionGameModeBase::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_AUnrealCompositionGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AUnrealCompositionGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AUnrealCompositionGameModeBase()
	{
		if (!Z_Registration_Info_UClass_AUnrealCompositionGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AUnrealCompositionGameModeBase.OuterSingleton, Z_Construct_UClass_AUnrealCompositionGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AUnrealCompositionGameModeBase.OuterSingleton;
	}
	template<> UNREALCOMPOSITION_API UClass* StaticClass<AUnrealCompositionGameModeBase>()
	{
		return AUnrealCompositionGameModeBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AUnrealCompositionGameModeBase);
	AUnrealCompositionGameModeBase::~AUnrealCompositionGameModeBase() {}
	struct Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealComposition_Source_UnrealComposition_UnrealCompositionGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealComposition_Source_UnrealComposition_UnrealCompositionGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AUnrealCompositionGameModeBase, AUnrealCompositionGameModeBase::StaticClass, TEXT("AUnrealCompositionGameModeBase"), &Z_Registration_Info_UClass_AUnrealCompositionGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AUnrealCompositionGameModeBase), 2596227984U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealComposition_Source_UnrealComposition_UnrealCompositionGameModeBase_h_3684321607(TEXT("/Script/UnrealComposition"),
		Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealComposition_Source_UnrealComposition_UnrealCompositionGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealComposition_Source_UnrealComposition_UnrealCompositionGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
