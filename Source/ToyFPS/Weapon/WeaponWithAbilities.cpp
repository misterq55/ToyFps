// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponWithAbilities.h"
#include "WeaponSystem/Weapon/WeaponAbility/WeaponAbility.h"
#include "AbilitySystemComponent.h"

AWeaponWithAbilities::AWeaponWithAbilities()
{
	// AbilitySystemComponent = CreateOptionalDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
}

// Called when the game starts or when spawned
void AWeaponWithAbilities::BeginPlay()
{
	Super::BeginPlay();
	ResetWeapon();
}

void AWeaponWithAbilities::Attack()
{
	if (!WeaponData.AttackAbility)
		return;

	// WeaponData.AttackAbility
}