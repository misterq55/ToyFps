// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraShakeBase.h"
#include "FpsCharacterBase.generated.h"

class UCameraComponent;
class AWeaponBase;

UCLASS()
class WEAPONSYSTEM_API AFpsCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFpsCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void SetCrouching(bool InCrouching) {
		bCrouching = InCrouching;
	}

	bool GetCrouching() {
		return bCrouching;
	}

	void SetSprinting(bool InSprinting) {
		bSprinting = InSprinting;
	}

	bool GetSprinting() {
		return bSprinting;
	}

	float GetSpreadCurrent() {
		return SpreadCurrent;
	}

	bool GetAimDownSight() {
		return bAimDownSight;
	}

	void SetAimDownSight(bool InAimDownSight) {
		bAimDownSight = InAimDownSight;
	}

	TObjectPtr<UCameraComponent> GetMainCamera() {
		return MainCameraComponent;
	}

	TObjectPtr<AWeaponBase> GetCurrentWeapon() {
		return CurrentWeapon;
	}

	UFUNCTION(BlueprintCallable, Category = ToyFpsCharacter)
		void IncreaseSpread(float InIncreaseAmount);

	UFUNCTION(BlueprintCallable, Category = ToyFpsCharacter)
		void DecreaseSpread(float InDecreaseAmount);

protected:
	const float SprintSpeed = 600;
	const float NormalSpeed = 300.f;
	float SpreadDecreaseSpeed = 1.f;

protected:
	UPROPERTY(Category = ToyFpsCharacter, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USkeletalMeshComponent> HeadMeshComponent;

	UPROPERTY(Category = ToyFpsCharacter, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCameraComponent> MainCameraComponent;

	UPROPERTY(Category = ToyFpsCharacter, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USkeletalMeshComponent> ArmsMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		bool bCrouching = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		bool bSprinting = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		bool bAimDownSight = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
		bool bReloading = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraShake, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UCameraShakeBase> RunningCameraShake;

	bool bRunningCameraShake = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<AWeaponBase> CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CrossHair, meta = (AllowPrivateAccess = "true"))
		float SpreadCurrent = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CrossHair, meta = (AllowPrivateAccess = "true"))
		float SpreadMax = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CrossHair, meta = (AllowPrivateAccess = "true"))
		float SpreadMin = 0.f;
};
