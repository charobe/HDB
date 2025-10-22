// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HDB_Multi/HDB_MultiGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHDB_MultiGameMode() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
HDB_MULTI_API UClass* Z_Construct_UClass_AHDB_MultiGameMode();
HDB_MULTI_API UClass* Z_Construct_UClass_AHDB_MultiGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_HDB_Multi();
// End Cross Module References

// Begin Class AHDB_MultiGameMode
void AHDB_MultiGameMode::StaticRegisterNativesAHDB_MultiGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AHDB_MultiGameMode);
UClass* Z_Construct_UClass_AHDB_MultiGameMode_NoRegister()
{
	return AHDB_MultiGameMode::StaticClass();
}
struct Z_Construct_UClass_AHDB_MultiGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "HDB_MultiGameMode.h" },
		{ "ModuleRelativePath", "HDB_MultiGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AHDB_MultiGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AHDB_MultiGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_HDB_Multi,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AHDB_MultiGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AHDB_MultiGameMode_Statics::ClassParams = {
	&AHDB_MultiGameMode::StaticClass,
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
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AHDB_MultiGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AHDB_MultiGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AHDB_MultiGameMode()
{
	if (!Z_Registration_Info_UClass_AHDB_MultiGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AHDB_MultiGameMode.OuterSingleton, Z_Construct_UClass_AHDB_MultiGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AHDB_MultiGameMode.OuterSingleton;
}
template<> HDB_MULTI_API UClass* StaticClass<AHDB_MultiGameMode>()
{
	return AHDB_MultiGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AHDB_MultiGameMode);
AHDB_MultiGameMode::~AHDB_MultiGameMode() {}
// End Class AHDB_MultiGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_jbong_Documents_GitHub_HDB_HDB_Multi_Source_HDB_Multi_HDB_MultiGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AHDB_MultiGameMode, AHDB_MultiGameMode::StaticClass, TEXT("AHDB_MultiGameMode"), &Z_Registration_Info_UClass_AHDB_MultiGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AHDB_MultiGameMode), 1292444322U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_jbong_Documents_GitHub_HDB_HDB_Multi_Source_HDB_Multi_HDB_MultiGameMode_h_1873356218(TEXT("/Script/HDB_Multi"),
	Z_CompiledInDeferFile_FID_Users_jbong_Documents_GitHub_HDB_HDB_Multi_Source_HDB_Multi_HDB_MultiGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_jbong_Documents_GitHub_HDB_HDB_Multi_Source_HDB_Multi_HDB_MultiGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
