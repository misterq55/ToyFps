// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmsAnimInstanceBase.h"

#include "KismetAnimationLibrary.h"
#include "WeaponSystem/Character/FpsCharacterBase.h"
#include "WeaponSystem/Weapon/WeaponBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UArmsAnimInstanceBase::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AFpsCharacterBase>(TryGetPawnOwner());
}

void UArmsAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!IsValid(OwningCharacter))
	{
		return;
	}

	const FVector velocity = OwningCharacter->GetVelocity();
	Speed = velocity.Length();

	Direction = UKismetAnimationLibrary::CalculateDirection(velocity, OwningCharacter->GetActorRotation());

	UCharacterMovementComponent* const characterMovement = OwningCharacter->GetCharacterMovement();
	if (!IsValid(characterMovement))
	{
		return;
	}

	bIsAccelarating = characterMovement->GetCurrentAcceleration().Length() > 0.f;
	EnableJump = characterMovement->IsFalling();
	bIsSprinting = OwningCharacter->IsSprinting();
	AimDownSight = OwningCharacter->IsAimingDownSight();
}

void UArmsAnimInstanceBase::SetWeaponData(const FWeaponData& InWeaponData)
{
	BlendSpace_WeaponIdle = InWeaponData.BlendSpace_WeaponIdle;
	BlendSpace_WeaponAdsIdle = InWeaponData.BlendSpace_WeaponAdsIdle;
	AnimSequence_WeaponJumpSequence1 = InWeaponData.AnimSequence_WeaponJumpSequence1;
	AnimSequence_WeaponJumpSequence2 = InWeaponData.AnimSequence_WeaponJumpSequence2;
	AnimSequence_WeaponJumpSequence3 = InWeaponData.AnimSequence_WeaponJumpSequence3;
	AnimSequence_WeaponWalk = InWeaponData.AnimSequence_WeaponWalk;
	AnimSequence_WeaponRun = InWeaponData.AnimSequence_WeaponRun;
}
