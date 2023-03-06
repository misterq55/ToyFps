// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponWithAbilities.h"
#include "WeaponSystem/Weapon/WeaponAbility/WeaponAbility.h"
#include "AbilitySystemComponent.h"

AWeaponWithAbilities::AWeaponWithAbilities()
{
	PrimaryActorTick.bCanEverTick = true;

	PrimaryWeapon = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("PrimaryWeapon"));
	Muzzle = CreateOptionalDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Eject = CreateOptionalDefaultSubobject<USceneComponent>(TEXT("Eject"));

	Muzzle->SetupAttachment(PrimaryWeapon);
	Eject->SetupAttachment(Muzzle);

	AbilitySystemComponent = CreateOptionalDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
}

// Called when the game starts or when spawned
void AWeaponWithAbilities::BeginPlay()
{
	Super::BeginPlay();
	ResetWeapon();
}

void AWeaponWithAbilities::ResetWeapon()
{
	Super::ResetWeapon();

	if (!WeaponData.AttackAbility)
		return;

	AttackAbilitySpec = AbilitySystemComponent->BuildAbilitySpecFromClass(WeaponData.AttackAbility, 0, -1);
	AbilitySystemComponent->GiveAbility(AttackAbilitySpec);
}

void AWeaponWithAbilities::Attack()
{
	if (!WeaponData.AttackAbility)
		return;

	AbilitySystemComponent->TryActivateAbility(AttackAbilitySpec.Handle);
}

void AWeaponWithAbilities::StopAttacking()
{
	if (!WeaponData.AttackAbility)
		return;

	AbilitySystemComponent->CancelAbility(AttackAbilitySpec.Ability);
}

UAbilitySystemComponent* AWeaponWithAbilities::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
