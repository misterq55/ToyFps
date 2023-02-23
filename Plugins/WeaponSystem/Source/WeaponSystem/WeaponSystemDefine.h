#pragma once
#include "CoreMinimal.h"
#include "WeaponSystemDefine.generated.h"

USTRUCT(BlueprintType)
struct WEAPONSYSTEM_API FWeaponData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		TSubclassOf<class AWeaponBase> WeaponClass;

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
		UAnimSequenceBase* AnimSequence_WeoponWalk = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimSequenceBase* AnimSequence_WeaponRun = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBlendSpace* BlendSpace_WeaponIdle = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBlendSpace* BlendSpace_WeaponAdsIdle = nullptr;
};