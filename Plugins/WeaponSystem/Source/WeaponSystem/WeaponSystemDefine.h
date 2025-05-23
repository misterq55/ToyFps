#pragma once
#include "CoreMinimal.h"
#include "WeaponSystem/Weapon/WeaponAbility/WeaponAbility.h"
#include "WeaponSystem/CrossHair/WeaponCrossHairWidget.h"
#include "WeaponSystemDefine.generated.h"

USTRUCT(BlueprintType)
struct WEAPONSYSTEM_API FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float AttackDamage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		int32 AmmoCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		int32 MaxAmmo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		FTransform MuzzleTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		FTransform EjectTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		float ReloadTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		float BulletSpread = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		float UndrawTime = 0.f;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USkeletalMesh> WeaponMesh;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UStaticMesh> WeaponPickUpMesh;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimSequenceBase* AnimSequence_WeoponJumpSequence1 = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimSequenceBase* AnimSequence_WeoponJumpSequence2 = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimSequenceBase* AnimSequence_WeoponJumpSequence3 = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimSequenceBase* AnimSequence_WeaponWalk = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimSequenceBase* AnimSequence_WeaponRun = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAnimSequenceBase* AnimSequence_WeaponFire = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AnimMontage_WeaponFire = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AnimMontage_AdsWeaponFire = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AnimMontage_WeaponReload = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AnimMontage_AdsWeaponReload = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AnimMontage_EmptyWeaponReload = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AnimMontage_AdsEmptyWeaponReload = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBlendSpace* BlendSpace_WeaponIdle = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBlendSpace* BlendSpace_WeaponAdsIdle = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UWeaponAbility> AttackAbility = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UWeaponAbility> ReloadAbility = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UWeaponCrossHairWidget> CrossHair = nullptr;
};