// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UnrealContainer/MyGameInstance.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyGameInstance() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UGameInstance();
	UNREALCONTAINER_API UClass* Z_Construct_UClass_UMyGameInstance();
	UNREALCONTAINER_API UClass* Z_Construct_UClass_UMyGameInstance_NoRegister();
	UNREALCONTAINER_API UClass* Z_Construct_UClass_UStudent_NoRegister();
	UNREALCONTAINER_API UScriptStruct* Z_Construct_UScriptStruct_FStudentData();
	UPackage* Z_Construct_UPackage__Script_UnrealContainer();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_StudentData;
class UScriptStruct* FStudentData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_StudentData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_StudentData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStudentData, Z_Construct_UPackage__Script_UnrealContainer(), TEXT("StudentData"));
	}
	return Z_Registration_Info_UScriptStruct_StudentData.OuterSingleton;
}
template<> UNREALCONTAINER_API UScriptStruct* StaticStruct<FStudentData>()
{
	return FStudentData::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FStudentData_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Order_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Order;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStudentData_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "MyGameInstance.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FStudentData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStudentData>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStudentData_Statics::NewProp_Name_MetaData[] = {
		{ "ModuleRelativePath", "MyGameInstance.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FStudentData_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FStudentData, Name), METADATA_PARAMS(Z_Construct_UScriptStruct_FStudentData_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStudentData_Statics::NewProp_Name_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStudentData_Statics::NewProp_Order_MetaData[] = {
		{ "ModuleRelativePath", "MyGameInstance.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FStudentData_Statics::NewProp_Order = { "Order", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FStudentData, Order), METADATA_PARAMS(Z_Construct_UScriptStruct_FStudentData_Statics::NewProp_Order_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStudentData_Statics::NewProp_Order_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FStudentData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStudentData_Statics::NewProp_Name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStudentData_Statics::NewProp_Order,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStudentData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_UnrealContainer,
		nullptr,
		&NewStructOps,
		"StudentData",
		sizeof(FStudentData),
		alignof(FStudentData),
		Z_Construct_UScriptStruct_FStudentData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStudentData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FStudentData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStudentData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FStudentData()
	{
		if (!Z_Registration_Info_UScriptStruct_StudentData.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_StudentData.InnerSingleton, Z_Construct_UScriptStruct_FStudentData_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_StudentData.InnerSingleton;
	}
	void UMyGameInstance::StaticRegisterNativesUMyGameInstance()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMyGameInstance);
	UClass* Z_Construct_UClass_UMyGameInstance_NoRegister()
	{
		return UMyGameInstance::StaticClass();
	}
	struct Z_Construct_UClass_UMyGameInstance_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Students_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Students_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Students;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UMyGameInstance_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UGameInstance,
		(UObject* (*)())Z_Construct_UPackage__Script_UnrealContainer,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMyGameInstance_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n *\n */" },
		{ "IncludePath", "MyGameInstance.h" },
		{ "ModuleRelativePath", "MyGameInstance.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UMyGameInstance_Statics::NewProp_Students_Inner = { "Students", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_UStudent_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMyGameInstance_Statics::NewProp_Students_MetaData[] = {
		{ "ModuleRelativePath", "MyGameInstance.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UMyGameInstance_Statics::NewProp_Students = { "Students", nullptr, (EPropertyFlags)0x0044000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UMyGameInstance, Students), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UMyGameInstance_Statics::NewProp_Students_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UMyGameInstance_Statics::NewProp_Students_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMyGameInstance_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMyGameInstance_Statics::NewProp_Students_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMyGameInstance_Statics::NewProp_Students,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UMyGameInstance_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMyGameInstance>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UMyGameInstance_Statics::ClassParams = {
		&UMyGameInstance::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UMyGameInstance_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UMyGameInstance_Statics::PropPointers),
		0,
		0x009000A8u,
		METADATA_PARAMS(Z_Construct_UClass_UMyGameInstance_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UMyGameInstance_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UMyGameInstance()
	{
		if (!Z_Registration_Info_UClass_UMyGameInstance.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMyGameInstance.OuterSingleton, Z_Construct_UClass_UMyGameInstance_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UMyGameInstance.OuterSingleton;
	}
	template<> UNREALCONTAINER_API UClass* StaticClass<UMyGameInstance>()
	{
		return UMyGameInstance::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UMyGameInstance);
	UMyGameInstance::~UMyGameInstance() {}
	struct Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealContainer_Source_UnrealContainer_MyGameInstance_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealContainer_Source_UnrealContainer_MyGameInstance_h_Statics::ScriptStructInfo[] = {
		{ FStudentData::StaticStruct, Z_Construct_UScriptStruct_FStudentData_Statics::NewStructOps, TEXT("StudentData"), &Z_Registration_Info_UScriptStruct_StudentData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStudentData), 4216803329U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealContainer_Source_UnrealContainer_MyGameInstance_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UMyGameInstance, UMyGameInstance::StaticClass, TEXT("UMyGameInstance"), &Z_Registration_Info_UClass_UMyGameInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMyGameInstance), 2186399548U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealContainer_Source_UnrealContainer_MyGameInstance_h_1643932531(TEXT("/Script/UnrealContainer"),
		Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealContainer_Source_UnrealContainer_MyGameInstance_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealContainer_Source_UnrealContainer_MyGameInstance_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealContainer_Source_UnrealContainer_MyGameInstance_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealContainer_Source_UnrealContainer_MyGameInstance_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
