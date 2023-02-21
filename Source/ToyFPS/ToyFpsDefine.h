#pragma once
#include "CoreMinimal.h"
#include "ToyFpsDefine.generated.h"

USTRUCT(BlueprintType)
struct TOYFPS_API FWeaponData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float AttackDamage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		int32 AmmoCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		int32 MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		FTransform MuzzleTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		FTransform EjectTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		float ReloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		float BuleetSpread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		float UndrawTime;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "PrimaryWeapon"))
		// TObjectPtr<USkeletalMesh> PrimaryWeaponMesh;
		USkeletalMesh* PrimaryWeaponMesh;

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