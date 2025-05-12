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

	FVector velocity = OwningCharacter->GetVelocity();
	Speed = velocity.Length();

	Direction = UKismetAnimationLibrary::CalculateDirection(velocity, OwningCharacter->GetActorRotation());

	UCharacterMovementComponent* characterMovement = OwningCharacter->GetCharacterMovement();
	if (!IsValid(characterMovement))
	{
		return;
	}

	bIsAccelarating = characterMovement->GetCurrentAcceleration().Length() > 0.f;
	EnableJump = characterMovement->IsFalling();
	bIsSprinting = OwningCharacter->GetSprinting();
	AimDownSight = OwningCharacter->GetAimDownSight();
}

void UArmsAnimInstanceBase::SetWeaponData(const FWeaponData& weaponData)
{
	BlendSpace_WeaponIdle = weaponData.BlendSpace_WeaponIdle;
	BlendSpace_WeaponAdsIdle = weaponData.BlendSpace_WeaponAdsIdle;
	AnimSequence_WeoponJumpSequence1 = weaponData.AnimSequence_WeoponJumpSequence1;
	AnimSequence_WeoponJumpSequence2 = weaponData.AnimSequence_WeoponJumpSequence2;
	AnimSequence_WeoponJumpSequence3 = weaponData.AnimSequence_WeoponJumpSequence3;
	AnimSequence_WeaponWalk = weaponData.AnimSequence_WeaponWalk;
	AnimSequence_WeaponRun = weaponData.AnimSequence_WeaponRun;
}
