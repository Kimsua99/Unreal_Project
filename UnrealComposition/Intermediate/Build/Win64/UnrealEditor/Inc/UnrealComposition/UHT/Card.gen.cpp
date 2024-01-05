// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UnrealComposition/Card.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCard() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UNREALCOMPOSITION_API UClass* Z_Construct_UClass_UCard();
	UNREALCOMPOSITION_API UClass* Z_Construct_UClass_UCard_NoRegister();
	UNREALCOMPOSITION_API UEnum* Z_Construct_UEnum_UnrealComposition_ECardType();
	UPackage* Z_Construct_UPackage__Script_UnrealComposition();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_ECardType;
	static UEnum* ECardType_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_ECardType.OuterSingleton)
		{
			Z_Registration_Info_UEnum_ECardType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_UnrealComposition_ECardType, Z_Construct_UPackage__Script_UnrealComposition(), TEXT("ECardType"));
		}
		return Z_Registration_Info_UEnum_ECardType.OuterSingleton;
	}
	template<> UNREALCOMPOSITION_API UEnum* StaticEnum<ECardType>()
	{
		return ECardType_StaticEnum();
	}
	struct Z_Construct_UEnum_UnrealComposition_ECardType_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_UnrealComposition_ECardType_Statics::Enumerators[] = {
		{ "ECardType::Student", (int64)ECardType::Student },
		{ "ECardType::Teacher", (int64)ECardType::Teacher },
		{ "ECardType::Staff", (int64)ECardType::Staff },
		{ "ECardType::Invalid", (int64)ECardType::Invalid },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_UnrealComposition_ECardType_Statics::Enum_MetaDataParams[] = {
		{ "Comment", "//\xc4\xab\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd0\xb7\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd. \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc2\xb0\xef\xbf\xbd \xef\xbf\xbd\xcf\xb9\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd.\n" },
		{ "Invalid.Name", "ECardType::Invalid" },
		{ "ModuleRelativePath", "Card.h" },
		{ "Staff.DisplayName", "For Staff" },
		{ "Staff.Name", "ECardType::Staff" },
		{ "Student.Comment", "//UMETA\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc5\xa9\xef\xbf\xbd\xce\xb7\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd DisplayName\xef\xbf\xbd\xcc\xb6\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc5\xb8 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd.\n" },
		{ "Student.DisplayName", "For Student" },
		{ "Student.Name", "ECardType::Student" },
		{ "Student.ToolTip", "UMETA\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc5\xa9\xef\xbf\xbd\xce\xb7\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd DisplayName\xef\xbf\xbd\xcc\xb6\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc5\xb8 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd." },
		{ "Teacher.DisplayName", "For Teacher" },
		{ "Teacher.Name", "ECardType::Teacher" },
		{ "ToolTip", "\xc4\xab\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd0\xb7\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd. \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc2\xb0\xef\xbf\xbd \xef\xbf\xbd\xcf\xb9\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd." },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_UnrealComposition_ECardType_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_UnrealComposition,
		nullptr,
		"ECardType",
		"ECardType",
		Z_Construct_UEnum_UnrealComposition_ECardType_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_UnrealComposition_ECardType_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_UnrealComposition_ECardType_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_UnrealComposition_ECardType_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_UnrealComposition_ECardType()
	{
		if (!Z_Registration_Info_UEnum_ECardType.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ECardType.InnerSingleton, Z_Construct_UEnum_UnrealComposition_ECardType_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_ECardType.InnerSingleton;
	}
	void UCard::StaticRegisterNativesUCard()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCard);
	UClass* Z_Construct_UClass_UCard_NoRegister()
	{
		return UCard::StaticClass();
	}
	struct Z_Construct_UClass_UCard_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FBytePropertyParams NewProp_CardType_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CardType_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_CardType;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Id_MetaData[];
#endif
		static const UECodeGen_Private::FUInt32PropertyParams NewProp_Id;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCard_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_UnrealComposition,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCard_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Card.h" },
		{ "ModuleRelativePath", "Card.h" },
	};
#endif
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UCard_Statics::NewProp_CardType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCard_Statics::NewProp_CardType_MetaData[] = {
		{ "ModuleRelativePath", "Card.h" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UCard_Statics::NewProp_CardType = { "CardType", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UCard, CardType), Z_Construct_UEnum_UnrealComposition_ECardType, METADATA_PARAMS(Z_Construct_UClass_UCard_Statics::NewProp_CardType_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCard_Statics::NewProp_CardType_MetaData)) }; // 197803830
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCard_Statics::NewProp_Id_MetaData[] = {
		{ "ModuleRelativePath", "Card.h" },
	};
#endif
	const UECodeGen_Private::FUInt32PropertyParams Z_Construct_UClass_UCard_Statics::NewProp_Id = { "Id", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::UInt32, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UCard, Id), METADATA_PARAMS(Z_Construct_UClass_UCard_Statics::NewProp_Id_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCard_Statics::NewProp_Id_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCard_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCard_Statics::NewProp_CardType_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCard_Statics::NewProp_CardType,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCard_Statics::NewProp_Id,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCard_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCard>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UCard_Statics::ClassParams = {
		&UCard::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UCard_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UCard_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCard_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCard_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCard()
	{
		if (!Z_Registration_Info_UClass_UCard.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCard.OuterSingleton, Z_Construct_UClass_UCard_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UCard.OuterSingleton;
	}
	template<> UNREALCOMPOSITION_API UClass* StaticClass<UCard>()
	{
		return UCard::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCard);
	UCard::~UCard() {}
	struct Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealComposition_Source_UnrealComposition_Card_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealComposition_Source_UnrealComposition_Card_h_Statics::EnumInfo[] = {
		{ ECardType_StaticEnum, TEXT("ECardType"), &Z_Registration_Info_UEnum_ECardType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 197803830U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealComposition_Source_UnrealComposition_Card_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UCard, UCard::StaticClass, TEXT("UCard"), &Z_Registration_Info_UClass_UCard, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCard), 1616069039U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealComposition_Source_UnrealComposition_Card_h_2924598520(TEXT("/Script/UnrealComposition"),
		Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealComposition_Source_UnrealComposition_Card_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealComposition_Source_UnrealComposition_Card_h_Statics::ClassInfo),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealComposition_Source_UnrealComposition_Card_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealTest_Unreal_Study_UnrealComposition_Source_UnrealComposition_Card_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
