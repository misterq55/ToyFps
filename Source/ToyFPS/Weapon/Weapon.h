// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToyFPS/ToyFpsDefine.h"
#include "Weapon.generated.h"

class UAnimSequenceBase;

UCLASS()
class TOYFPS_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = Weapon)
		virtual void Attack() {}

	UFUNCTION(BlueprintCallable, Category = Weapon)
		virtual void Reload() {}

	UFUNCTION(BlueprintCallable, Category = Weapon)
		virtual void Undraw() {}

	UFUNCTION(BlueprintCallable, Category = Weapon)
		virtual void Draw() {}

	UFUNCTION(BlueprintCallable, Category = Weapon)
		virtual void Equipe() {}

	UFUNCTION(BlueprintCallable, Category = Weapon)
		virtual void StopAttacking() {}

	UFUNCTION(BlueprintCallable, Category = Weapon)
		virtual void SecondartAttack() {}

	UFUNCTION(BlueprintCallable, Category = Weapon)
		virtual void SniperZoom(bool Toggle) {}

	UFUNCTION(BlueprintCallable, Category = Weapon)
		virtual void HideMuzzleFlash() {}

	UFUNCTION(BlueprintCallable, Category = Weapon)
		virtual void UnHideMuzzleFlash() {}

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void LineTrace(FVector& OutMuzzleLocation, FVector& OutImactPoint, FRotator& ProjectileRotation);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetBulletSpread() {
		return BulletSpread;
	}

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		float BulletSpread = 0.f;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayName = "PrimaryWeapon"))
		TObjectPtr<USkeletalMeshComponent> PrimaryWeapon;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayName = "Muzzle"))
		TObjectPtr<USceneComponent> Muzzle;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayName = "Eject"))
		TObjectPtr<USceneComponent> Eject;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FRotator OGControllerRotation;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FRotator PostRecoilRotation;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float MaxRecoilThreshold;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float ReloadTime;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float AttackDamage = 0.f;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FWeaponData WeaponData;

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
