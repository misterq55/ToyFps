// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ArmsAnimInstance.generated.h"

/**
 * 
 */

class AToyFpsCharacter;
UCLASS()
class TOYFPS_API UArmsAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = ArmAnimation)
	AToyFpsCharacter* OwningCharacter = nullptr;

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
};
