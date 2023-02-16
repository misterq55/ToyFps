// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ToyFpsCharacter.generated.h"

class UCameraComponent;
class UCameraShakeBase;
class UChildActorComponent;
class AWeapon;

UCLASS()
class TOYFPS_API AToyFpsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AToyFpsCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void DoCrouching();
	void StopCrouching();

	void Sprint();
	void StopSprinting();

	void Attack();
	void StopAttacking();

	void Reload();
	
	void DoAimimgDownSight();
	void StopAimingDownSight();

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

	UFUNCTION(BlueprintCallable, Category = ToyFpsCharacter)
		void IncreaseSpread(float InIncreaseAmount);
	
	UFUNCTION(BlueprintCallable, Category = ToyFpsCharacter)
		void DecreaseSpread(float InDecreaseAmount);

private:
	const float SprintSpeed = 600;
	const float NormalSpeed = 300.f;
	float SpreadDecreaseSpeed = 1.f;
	

private:
	UPROPERTY(Category = ToyFpsCharacter, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USkeletalMeshComponent> HeadMeshComponent;

	UPROPERTY(Category = ToyFpsCharacter, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCameraComponent> MainCameraComponent;

	UPROPERTY(Category = ToyFpsCharacter, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USkeletalMeshComponent> ArmsMeshComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;

	/** Crouch Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* CrouchAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* SprintAction;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* AttackAction;

	/** Reload Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* ReloadAction;

	/** Meele Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MeeleAttackAction;

	/** Aim Down Sight Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* AimDownSightAction;

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
		TObjectPtr<UChildActorComponent> CurrentWeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AWeapon> CurrentWeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CrossHair, meta = (AllowPrivateAccess = "true"))
		float SpreadCurrent = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CrossHair, meta = (AllowPrivateAccess = "true"))
		float SpreadMax = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CrossHair, meta = (AllowPrivateAccess = "true"))
		float SpreadMin = 0.f;
};
