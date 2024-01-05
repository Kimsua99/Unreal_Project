// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UnrealTest/UnrealTestGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUnrealTestGameModeBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UNREALTEST_API UClass* Z_Construct_UClass_AUnrealTestGameModeBase();
	UNREALTEST_API UClass* Z_Construct_UClass_AUnrealTestGameModeBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_UnrealTest();
// End Cross Module References
	void AUnrealTestGameModeBase::StaticRegisterNativesAUnrealTestGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AUnrealTestGameModeBase);
	UClass* Z_Construct_UClass_AUnrealTestGameModeBase_NoRegister()
	{
		return AUnrealTestGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_AUnrealTestGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AUnrealTestGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_UnrealTest,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AUnrealTestGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "UnrealTestGameModeBase.h" },
		{ "ModuleRelativePath", "UnrealTestGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AUnrealTestGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AUnrealTestGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AUnrealTestGameModeBase_Statics::ClassParams = {
		&AUnrealTestGameModeBase::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_AUnrealTestGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AUnrealTestGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AUnrealTestGameModeBase()
	{
		if (!Z_Registration_Info_UClass_AUnrealTestGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AUnrealTestGameModeBase.OuterSingleton, Z_Construct_UClass_AUnrealTestGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AUnrealTestGameModeBase.OuterSingleton;
	}
	template<> UNREALTEST_API UClass* StaticClass<AUnrealTestGameModeBase>()
	{
		return AUnrealTestGameModeBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AUnrealTestGameModeBase);
	AUnrealTestGameModeBase::~AUnrealTestGameModeBase() {}
	struct Z_CompiledInDeferFile_FID_UnrealTest_UnrealTest_Source_UnrealTest_UnrealTestGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_UnrealTest_Source_UnrealTest_UnrealTestGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AUnrealTestGameModeBase, AUnrealTestGameModeBase::StaticClass, TEXT("AUnrealTestGameModeBase"), &Z_Registration_Info_UClass_AUnrealTestGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AUnrealTestGameModeBase), 3225868929U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_UnrealTest_Source_UnrealTest_UnrealTestGameModeBase_h_1824422351(TEXT("/Script/UnrealTest"),
		Z_CompiledInDeferFile_FID_UnrealTest_UnrealTest_Source_UnrealTest_UnrealTestGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealTest_UnrealTest_Source_UnrealTest_UnrealTestGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
