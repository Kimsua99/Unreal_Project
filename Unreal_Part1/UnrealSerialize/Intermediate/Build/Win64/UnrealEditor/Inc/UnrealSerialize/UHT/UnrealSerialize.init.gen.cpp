// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUnrealSerialize_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_UnrealSerialize;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_UnrealSerialize()
	{
		if (!Z_Registration_Info_UPackage__Script_UnrealSerialize.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/UnrealSerialize",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0xDD5432DE,
				0xB337E80A,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_UnrealSerialize.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_UnrealSerialize.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_UnrealSerialize(Z_Construct_UPackage__Script_UnrealSerialize, TEXT("/Script/UnrealSerialize"), Z_Registration_Info_UPackage__Script_UnrealSerialize, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xDD5432DE, 0xB337E80A));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
