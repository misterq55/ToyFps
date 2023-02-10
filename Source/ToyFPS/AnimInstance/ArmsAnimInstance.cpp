// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmsAnimInstance.h"
#include "ToyFPS/Character/ToyFpsCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UArmsAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AToyFpsCharacter>(TryGetPawnOwner());
}

void UArmsAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
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
}