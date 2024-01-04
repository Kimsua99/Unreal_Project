// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ArenaBattle/ArenaBattleGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeArenaBattleGameModeBase() {}
// Cross Module References
	ARENABATTLE_API UClass* Z_Construct_UClass_AArenaBattleGameModeBase();
	ARENABATTLE_API UClass* Z_Construct_UClass_AArenaBattleGameModeBase_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_ArenaBattle();
// End Cross Module References
	void AArenaBattleGameModeBase::StaticRegisterNativesAArenaBattleGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AArenaBattleGameModeBase);
	UClass* Z_Construct_UClass_AArenaBattleGameModeBase_NoRegister()
	{
		return AArenaBattleGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_AArenaBattleGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AArenaBattleGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_ArenaBattle,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AArenaBattleGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "ArenaBattleGameModeBase.h" },
		{ "ModuleRelativePath", "ArenaBattleGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AArenaBattleGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AArenaBattleGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AArenaBattleGameModeBase_Statics::ClassParams = {
		&AArenaBattleGameModeBase::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_AArenaBattleGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AArenaBattleGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AArenaBattleGameModeBase()
	{
		if (!Z_Registration_Info_UClass_AArenaBattleGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AArenaBattleGameModeBase.OuterSingleton, Z_Construct_UClass_AArenaBattleGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AArenaBattleGameModeBase.OuterSingleton;
	}
	template<> ARENABATTLE_API UClass* StaticClass<AArenaBattleGameModeBase>()
	{
		return AArenaBattleGameModeBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AArenaBattleGameModeBase);
	AArenaBattleGameModeBase::~AArenaBattleGameModeBase() {}
	struct Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_Unreal_Part2_ArenaBattle_Source_ArenaBattle_ArenaBattleGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_Unreal_Part2_ArenaBattle_Source_ArenaBattle_ArenaBattleGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AArenaBattleGameModeBase, AArenaBattleGameModeBase::StaticClass, TEXT("AArenaBattleGameModeBase"), &Z_Registration_Info_UClass_AArenaBattleGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AArenaBattleGameModeBase), 350211408U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_Unreal_Part2_ArenaBattle_Source_ArenaBattle_ArenaBattleGameModeBase_h_4016062629(TEXT("/Script/ArenaBattle"),
		Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_Unreal_Part2_ArenaBattle_Source_ArenaBattle_ArenaBattleGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_Unreal_Part2_ArenaBattle_Source_ArenaBattle_ArenaBattleGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
