// Fill out your copyright notice in the Description page of Project Settings.


#include "ToyFpsCharacterWithWeaponBP.h"
#include "ToyFPS/Weapon/Weapon.h"
#include "WeaponSystem/AnimInstance/ArmsAnimInstanceBase.h"

AToyFpsCharacterWithWeaponBP::AToyFpsCharacterWithWeaponBP()
	: Super()
{
	CurrentWeaponComponent = CreateOptionalDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));

	if (!CurrentWeaponComponent)
		return;

	CurrentWeaponComponent->SetChildActorClass(CurrentWeaponClass);
	CurrentWeaponComponent->SetupAttachment(ArmsMeshComponent, TEXT("WeaponSocket"));
}

void AToyFpsCharacterWithWeaponBP::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeaponComponent->CreateChildActor();
	CurrentWeapon = Cast<AWeapon>(CurrentWeaponComponent->GetChildActor());

	UArmsAnimInstanceBase* ArmsAnimInstance = Cast<UArmsAnimInstanceBase>(ArmsMeshComponent->GetAnimInstance());
	ArmsAnimInstance->SetWeaponData(CurrentWeapon->GetWeaponData());
}