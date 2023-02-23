// Fill out your copyright notice in the Description page of Project Settings.


#include "ToyFpsCharacterWithWeaponAsset.h"
#include "WeaponSystem/Weapon/WeaponAsset.h"
#include "ToyFPS/Weapon/Weapon.h"
#include "ToyFPS/AnimInstance/ArmsAnimInstance.h"

AToyFpsCharacterWithWeaponAsset::AToyFpsCharacterWithWeaponAsset()
	: Super()
{
	WeaponPivot = CreateOptionalDefaultSubobject<USceneComponent>(TEXT("Weapon"));

	if (!WeaponPivot)
		return;

	WeaponPivot->SetupAttachment(ArmsMeshComponent, TEXT("WeaponSocket"));
}

void AToyFpsCharacterWithWeaponAsset::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeapon = Cast<AWeapon>(GetWorld()->SpawnActor(WeaponAsset->GetWeaponData().WeaponClass));
	CurrentWeapon->SetWeaponData(WeaponAsset->GetWeaponData());
	CurrentWeapon->AttachToComponent(WeaponPivot, FAttachmentTransformRules::KeepRelativeTransform);
	CurrentWeapon->ResetWeapon();

	UArmsAnimInstance* ArmsAnimInstance = Cast<UArmsAnimInstance>(ArmsMeshComponent->GetAnimInstance());
	ArmsAnimInstance->SetWeaponData(CurrentWeapon);
}