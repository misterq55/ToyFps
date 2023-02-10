// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayName = "PrimaryWeapon"))
		TObjectPtr<USkeletalMeshComponent> PrimaryWeapon;
};
