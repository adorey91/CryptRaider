// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "CryptRaiderPickUpComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class ACryptRaiderCharacter;
class UPrimitiveComponent;
struct FHitResult;
#ifdef CRYPTRAIDER_CryptRaiderPickUpComponent_generated_h
#error "CryptRaiderPickUpComponent.generated.h already included, missing '#pragma once' in CryptRaiderPickUpComponent.h"
#endif
#define CRYPTRAIDER_CryptRaiderPickUpComponent_generated_h

#define FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderPickUpComponent_h_12_DELEGATE \
CRYPTRAIDER_API void FOnPickUp_DelegateWrapper(const FMulticastScriptDelegate& OnPickUp, ACryptRaiderCharacter* PickUpCharacter);


#define FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderPickUpComponent_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnSphereBeginOverlap);


#define FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderPickUpComponent_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCryptRaiderPickUpComponent(); \
	friend struct Z_Construct_UClass_UCryptRaiderPickUpComponent_Statics; \
public: \
	DECLARE_CLASS(UCryptRaiderPickUpComponent, USphereComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/CryptRaider"), NO_API) \
	DECLARE_SERIALIZER(UCryptRaiderPickUpComponent)


#define FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderPickUpComponent_h_17_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UCryptRaiderPickUpComponent(UCryptRaiderPickUpComponent&&); \
	UCryptRaiderPickUpComponent(const UCryptRaiderPickUpComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCryptRaiderPickUpComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCryptRaiderPickUpComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UCryptRaiderPickUpComponent) \
	NO_API virtual ~UCryptRaiderPickUpComponent();


#define FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderPickUpComponent_h_14_PROLOG
#define FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderPickUpComponent_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderPickUpComponent_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderPickUpComponent_h_17_INCLASS_NO_PURE_DECLS \
	FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderPickUpComponent_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> CRYPTRAIDER_API UClass* StaticClass<class UCryptRaiderPickUpComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_GithubRepos_CryptRaider_CryptRaider_Source_CryptRaider_CryptRaiderPickUpComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
