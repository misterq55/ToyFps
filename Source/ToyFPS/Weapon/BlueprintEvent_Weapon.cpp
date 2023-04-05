// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintEvent_Weapon.h"

ABlueprintEvent_Weapon::ABlueprintEvent_Weapon()
{
	PrimaryActorTick.bCanEverTick = true;

	PrimaryWeapon = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("PrimaryWeapon"));
	Muzzle = CreateOptionalDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Eject = CreateOptionalDefaultSubobject<USceneComponent>(TEXT("Eject"));

	Muzzle->SetupAttachment(PrimaryWeapon);
	Eject->SetupAttachment(Muzzle);
}

void ABlueprintEvent_Weapon::Attack()
{
	Attack_BluePrint();
}

void ABlueprintEvent_Weapon::Reload()
{
	Reload_BluePrint();
}

void ABlueprintEvent_Weapon::Undraw()
{
	Undraw_BluePrint();
}

void ABlueprintEvent_Weapon::Draw()
{
	Draw_BluePrint();
}

void ABlueprintEvent_Weapon::Equipe()
{
	Equipe_BluePrint();
}

void ABlueprintEvent_Weapon::StopAttacking()
{
	StopAttacking_BluePrint();
}

void ABlueprintEvent_Weapon::SecondartAttack()
{
	SecondartAttack_BluePrint();
}

void ABlueprintEvent_Weapon::SniperZoom(bool Toggle)
{
	SniperZoom_BluePrint(Toggle);
}

void ABlueprintEvent_Weapon::HideMuzzleFlash()
{
	HideMuzzleFlash_BluePrint();
}

void ABlueprintEvent_Weapon::UnHideMuzzleFlash()
{
	UnhideMuzzleFlash_BluePrint();
}

void ABlueprintEvent_Weapon::Attack_BluePrint_Implementation()
{
}

void ABlueprintEvent_Weapon::Reload_BluePrint_Implementation()
{
}

void ABlueprintEvent_Weapon::Undraw_BluePrint_Implementation()
{
}

void ABlueprintEvent_Weapon::Draw_BluePrint_Implementation()
{
}

void ABlueprintEvent_Weapon::Equipe_BluePrint_Implementation()
{
}

void ABlueprintEvent_Weapon::StopAttacking_BluePrint_Implementation()
{
}

void ABlueprintEvent_Weapon::SecondartAttack_BluePrint_Implementation()
{
}

void ABlueprintEvent_Weapon::SniperZoom_BluePrint_Implementation(bool Toggle)
{
}

void ABlueprintEvent_Weapon::HideMuzzleFlash_BluePrint_Implementation()
{
}

void ABlueprintEvent_Weapon::UnhideMuzzleFlash_BluePrint_Implementation()
{
}