// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UnrealDelegate/Person.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePerson() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UNREALDELEGATE_API UClass* Z_Construct_UClass_UCard_NoRegister();
	UNREALDELEGATE_API UClass* Z_Construct_UClass_UPerson();
	UNREALDELEGATE_API UClass* Z_Construct_UClass_UPerson_NoRegister();
	UPackage* Z_Construct_UPackage__Script_UnrealDelegate();
// End Cross Module References
	void UPerson::StaticRegisterNativesUPerson()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UPerson);
	UClass* Z_Construct_UClass_UPerson_NoRegister()
	{
		return UPerson::StaticClass();
	}
	struct Z_Construct_UClass_UPerson_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Card_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Card;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UPerson_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_UnrealDelegate,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPerson_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n *\n */" },
		{ "IncludePath", "Person.h" },
		{ "ModuleRelativePath", "Person.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPerson_Statics::NewProp_Name_MetaData[] = {
		{ "ModuleRelativePath", "Person.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UPerson_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UPerson, Name), METADATA_PARAMS(Z_Construct_UClass_UPerson_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPerson_Statics::NewProp_Name_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPerson_Statics::NewProp_Card_MetaData[] = {
		{ "ModuleRelativePath", "Person.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UPerson_Statics::NewProp_Card = { "Card", nullptr, (EPropertyFlags)0x0024080000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UPerson, Card), Z_Construct_UClass_UCard_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UPerson_Statics::NewProp_Card_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPerson_Statics::NewProp_Card_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UPerson_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPerson_Statics::NewProp_Name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPerson_Statics::NewProp_Card,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UPerson_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPerson>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UPerson_Statics::ClassParams = {
		&UPerson::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UPerson_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UPerson_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UPerson_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UPerson_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UPerson()
	{
		if (!Z_Registration_Info_UClass_UPerson.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UPerson.OuterSingleton, Z_Construct_UClass_UPerson_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UPerson.OuterSingleton;
	}
	template<> UNREALDELEGATE_API UClass* StaticClass<UPerson>()
	{
		return UPerson::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UPerson);
	UPerson::~UPerson() {}
	struct Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealDelegate_Source_UnrealDelegate_Person_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealDelegate_Source_UnrealDelegate_Person_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UPerson, UPerson::StaticClass, TEXT("UPerson"), &Z_Registration_Info_UClass_UPerson, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UPerson), 3870936162U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealDelegate_Source_UnrealDelegate_Person_h_1600737351(TEXT("/Script/UnrealDelegate"),
		Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealDelegate_Source_UnrealDelegate_Person_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealDelegate_Source_UnrealDelegate_Person_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
