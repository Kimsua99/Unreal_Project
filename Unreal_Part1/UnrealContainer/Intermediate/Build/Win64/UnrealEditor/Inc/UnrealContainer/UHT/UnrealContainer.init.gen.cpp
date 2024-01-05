// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUnrealContainer_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_UnrealContainer;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_UnrealContainer()
	{
		if (!Z_Registration_Info_UPackage__Script_UnrealContainer.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/UnrealContainer",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x81C27DA3,
				0xB4715936,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_UnrealContainer.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_UnrealContainer.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_UnrealContainer(Z_Construct_UPackage__Script_UnrealContainer, TEXT("/Script/UnrealContainer"), Z_Registration_Info_UPackage__Script_UnrealContainer, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x81C27DA3, 0xB4715936));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
