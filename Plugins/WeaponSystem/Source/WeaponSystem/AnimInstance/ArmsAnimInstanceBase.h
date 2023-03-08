// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WeaponSystem/WeaponSystemDefine.h"
#include "ArmsAnimInstanceBase.generated.h"

/**
 * 
 */

class AFpsCharacterBase;
class AWeaponBase;

UCLASS()
class WEAPONSYSTEM_API UArmsAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	// void SetWeaponData(AWeaponBase* InWeapon);
	void SetWeaponData(const FWeaponData& InWeaponData);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = ArmAnimation)
		AFpsCharacterBase* OwningCharacter = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = ArmAnimation)
		float Direction = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = ArmAnimation)
		bool IsAccelarating = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = ArmAnimation)
		float Speed = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = ArmAnimation)
		float RunningMotionLimitSpeed = 400.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = ArmAnimation)
		bool AimDownSight = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = ArmAnimation)
		bool IsSprinting = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = ArmAnimation)
		bool EnableJump = false;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UAnimSequenceBase* AnimSequence_WeoponJumpSequence1 = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UAnimSequenceBase* AnimSequence_WeoponJumpSequence2 = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UAnimSequenceBase* AnimSequence_WeoponJumpSequence3 = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UAnimSequenceBase* AnimSequence_WeoponWalk = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UAnimSequenceBase* AnimSequence_WeaponRun = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UBlendSpace* BlendSpace_WeaponIdle = nullptr;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UBlendSpace* BlendSpace_WeaponAdsIdle = nullptr;
};
