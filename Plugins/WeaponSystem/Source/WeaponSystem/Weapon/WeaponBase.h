// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponSystem/WeaponSystemDefine.h"
#include "WeaponBase.generated.h"

class AFpsCharacterBase;
class UTimelineComponent;

UCLASS()
class WEAPONSYSTEM_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

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
		virtual void LineTrace(FVector& OutMuzzleLocation, FVector& OutImactPoint, FRotator& ProjectileRotation);

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void ReloadAmmo();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTickIfViewportsOnly() const
	{
		return true;
	}

	FWeaponData& GetWeaponData() {
		return WeaponData;
	}

	void SetWeaponData(FWeaponData InWeaponData);
	void SetOwningCharacter(AFpsCharacterBase* InCharacter) {
		OwningCharacter = InCharacter;
	}

	UFUNCTION(BlueprintCallable, Category = Weapon)
	AFpsCharacterBase* GetOwningCharacter() {
		return OwningCharacter;
	};

	virtual void ResetWeapon(const FWeaponData& InWeaponData);

protected:

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayName = "PrimaryWeapon"))
		TObjectPtr<USkeletalMeshComponent> PrimaryWeapon;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayName = "Muzzle"))
		TObjectPtr<USceneComponent> Muzzle;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayName = "Eject"))
		TObjectPtr<USceneComponent> Eject;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UTimelineComponent> RecoilPattern;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FRotator OGControllerRotation;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FRotator PostRecoilRotation;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float MaxRecoilThreshold;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FWeaponData WeaponData;

private:
	TObjectPtr<AFpsCharacterBase> OwningCharacter;
};
