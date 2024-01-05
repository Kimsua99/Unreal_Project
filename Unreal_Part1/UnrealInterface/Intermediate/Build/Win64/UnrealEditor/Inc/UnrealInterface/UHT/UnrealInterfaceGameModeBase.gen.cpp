// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UnrealInterface/UnrealInterfaceGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUnrealInterfaceGameModeBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UNREALINTERFACE_API UClass* Z_Construct_UClass_AUnrealInterfaceGameModeBase();
	UNREALINTERFACE_API UClass* Z_Construct_UClass_AUnrealInterfaceGameModeBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_UnrealInterface();
// End Cross Module References
	void AUnrealInterfaceGameModeBase::StaticRegisterNativesAUnrealInterfaceGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AUnrealInterfaceGameModeBase);
	UClass* Z_Construct_UClass_AUnrealInterfaceGameModeBase_NoRegister()
	{
		return AUnrealInterfaceGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_AUnrealInterfaceGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AUnrealInterfaceGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_UnrealInterface,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AUnrealInterfaceGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "UnrealInterfaceGameModeBase.h" },
		{ "ModuleRelativePath", "UnrealInterfaceGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AUnrealInterfaceGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AUnrealInterfaceGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AUnrealInterfaceGameModeBase_Statics::ClassParams = {
		&AUnrealInterfaceGameModeBase::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_AUnrealInterfaceGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AUnrealInterfaceGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AUnrealInterfaceGameModeBase()
	{
		if (!Z_Registration_Info_UClass_AUnrealInterfaceGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AUnrealInterfaceGameModeBase.OuterSingleton, Z_Construct_UClass_AUnrealInterfaceGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AUnrealInterfaceGameModeBase.OuterSingleton;
	}
	template<> UNREALINTERFACE_API UClass* StaticClass<AUnrealInterfaceGameModeBase>()
	{
		return AUnrealInterfaceGameModeBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AUnrealInterfaceGameModeBase);
	AUnrealInterfaceGameModeBase::~AUnrealInterfaceGameModeBase() {}
	struct Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealInterface_Source_UnrealInterface_UnrealInterfaceGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealInterface_Source_UnrealInterface_UnrealInterfaceGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AUnrealInterfaceGameModeBase, AUnrealInterfaceGameModeBase::StaticClass, TEXT("AUnrealInterfaceGameModeBase"), &Z_Registration_Info_UClass_AUnrealInterfaceGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AUnrealInterfaceGameModeBase), 3974485398U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealInterface_Source_UnrealInterface_UnrealInterfaceGameModeBase_h_627554677(TEXT("/Script/UnrealInterface"),
		Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealInterface_Source_UnrealInterface_UnrealInterfaceGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealInterface_Source_UnrealInterface_UnrealInterfaceGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
