// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponWithAbilities.h"
#include "WeaponSystem/Weapon/WeaponAbility/WeaponAbility.h"

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