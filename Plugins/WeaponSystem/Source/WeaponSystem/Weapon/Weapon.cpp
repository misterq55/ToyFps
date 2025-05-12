// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "WeaponSystem/Weapon/WeaponAbility/WeaponAbility.h"
#include "Components/TimelineComponent.h"
#include "AbilitySystemComponent.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	PrimaryWeapon = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("PrimaryWeapon"));
	Muzzle = CreateOptionalDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Eject = CreateOptionalDefaultSubobject<USceneComponent>(TEXT("Eject"));

	RecoilPattern = CreateOptionalDefaultSubobject<UTimelineComponent>(TEXT("RecoilPattern"));

	Muzzle->SetupAttachment(PrimaryWeapon);
	Eject->SetupAttachment(Muzzle);

	AbilitySystemComponent = CreateOptionalDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	ResetWeapon(WeaponData);
}

void AWeapon::ResetWeapon(const FWeaponData& InWeaponData)
{
	Super::ResetWeapon(InWeaponData);

	WeaponData = InWeaponData;

	if (!WeaponData.AttackAbility)
		return;

	AttackAbilitySpec = AbilitySystemComponent->BuildAbilitySpecFromClass(WeaponData.AttackAbility, 0, -1);
	AbilitySystemComponent->GiveAbility(AttackAbilitySpec);

	ReloadAbilitySpec = AbilitySystemComponent->BuildAbilitySpecFromClass(WeaponData.ReloadAbility, 0, -1);
	AbilitySystemComponent->GiveAbility(ReloadAbilitySpec);
}

void AWeapon::Attack()
{
	if (!WeaponData.AttackAbility)
		return;

	AbilitySystemComponent->TryActivateAbility(AttackAbilitySpec.Handle);
}

void AWeapon::Reload()
{
	if (!WeaponData.ReloadAbility)
		return;

	AbilitySystemComponent->TryActivateAbility(ReloadAbilitySpec.Handle);
}

void AWeapon::StopAttacking()
{
	if (!WeaponData.AttackAbility)
		return;

	AbilitySystemComponent->CancelAbility(AttackAbilitySpec.Ability);
}

UAbilitySystemComponent* AWeapon::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
