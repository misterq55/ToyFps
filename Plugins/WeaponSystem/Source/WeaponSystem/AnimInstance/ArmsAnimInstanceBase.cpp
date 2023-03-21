// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmsAnimInstanceBase.h"
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

	if (!OwningCharacter)
		return;

	FVector Velocity = OwningCharacter->GetVelocity();
	Speed = Velocity.Length();

	Direction = CalculateDirection(Velocity, OwningCharacter->GetActorRotation());

	UCharacterMovementComponent* CharacterMovement = OwningCharacter->GetCharacterMovement();
	if (!CharacterMovement)
		return;

	if (CharacterMovement->GetCurrentAcceleration().Length() > 0.f)
		IsAccelarating = true;
	else
		IsAccelarating = false;

	if (CharacterMovement->IsFalling())
		EnableJump = true;
	else
		EnableJump = false;

	IsSprinting = OwningCharacter->GetSprinting();
	AimDownSight = OwningCharacter->GetAimDownSight();
}

void UArmsAnimInstanceBase::SetWeaponData(const FWeaponData& InWeaponData)
{
	BlendSpace_WeaponIdle = InWeaponData.BlendSpace_WeaponIdle;
	BlendSpace_WeaponAdsIdle = InWeaponData.BlendSpace_WeaponAdsIdle;
	AnimSequence_WeoponJumpSequence1 = InWeaponData.AnimSequence_WeoponJumpSequence1;
	AnimSequence_WeoponJumpSequence2 = InWeaponData.AnimSequence_WeoponJumpSequence2;
	AnimSequence_WeoponJumpSequence3 = InWeaponData.AnimSequence_WeoponJumpSequence3;
	AnimSequence_WeaponWalk = InWeaponData.AnimSequence_WeaponWalk;
	AnimSequence_WeaponRun = InWeaponData.AnimSequence_WeaponRun;
}
