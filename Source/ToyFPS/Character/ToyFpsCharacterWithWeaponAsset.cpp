// Fill out your copyright notice in the Description page of Project Settings.


#include "ToyFpsCharacterWithWeaponAsset.h"
#include "WeaponSystem/Weapon/WeaponAsset.h"
#include "WeaponSystem/Weapon/WeaponWithAbilities.h"
#include "WeaponSystem/AnimInstance/ArmsAnimInstanceBase.h"

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

	CurrentWeapon = Cast<AWeaponBase>(GetWorld()->SpawnActor(AWeaponWithAbilities::StaticClass()));

	if (!CurrentWeapon)
		return;

	CurrentWeapon->SetOwningCharacter(this);
	CurrentWeapon->SetWeaponData(WeaponAsset->GetWeaponData());
	CurrentWeapon->AttachToComponent(WeaponPivot, FAttachmentTransformRules::KeepRelativeTransform);
	CurrentWeapon->ResetWeapon(WeaponAsset->GetWeaponData());

	UArmsAnimInstanceBase* ArmsAnimInstance = Cast<UArmsAnimInstanceBase>(ArmsMeshComponent->GetAnimInstance());
	ArmsAnimInstance->SetWeaponData(CurrentWeapon->GetWeaponData());

	UWeaponCrossHairWidget* CrossHair = CreateWidget<UWeaponCrossHairWidget>(GetWorld(), WeaponAsset->GetWeaponData().CrossHair);
	
	if (CrossHair)
		CrossHair->AddToViewport();
}