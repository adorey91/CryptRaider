// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "CryptRaiderWeaponComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class ACryptRaiderCharacter;
#ifdef CRYPTRAIDER_CryptRaiderWeaponComponent_generated_h
#error "CryptRaiderWeaponComponent.generated.h already included, missing '#pragma once' in CryptRaiderWeaponComponent.h"
#endif
#define CRYPTRAIDER_CryptRaiderWeaponComponent_generated_h

#define FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderWeaponComponent_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execEndPlay); \
	DECLARE_FUNCTION(execFire); \
	DECLARE_FUNCTION(execAttachWeapon);


#define FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderWeaponComponent_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCryptRaiderWeaponComponent(); \
	friend struct Z_Construct_UClass_UCryptRaiderWeaponComponent_Statics; \
public: \
	DECLARE_CLASS(UCryptRaiderWeaponComponent, USkeletalMeshComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/CryptRaider"), NO_API) \
	DECLARE_SERIALIZER(UCryptRaiderWeaponComponent)


#define FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderWeaponComponent_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UCryptRaiderWeaponComponent(UCryptRaiderWeaponComponent&&); \
	UCryptRaiderWeaponComponent(const UCryptRaiderWeaponComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCryptRaiderWeaponComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCryptRaiderWeaponComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UCryptRaiderWeaponComponent) \
	NO_API virtual ~UCryptRaiderWeaponComponent();


#define FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderWeaponComponent_h_11_PROLOG
#define FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderWeaponComponent_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderWeaponComponent_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderWeaponComponent_h_14_INCLASS_NO_PURE_DECLS \
	FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderWeaponComponent_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> CRYPTRAIDER_API UClass* StaticClass<class UCryptRaiderWeaponComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderWeaponComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
