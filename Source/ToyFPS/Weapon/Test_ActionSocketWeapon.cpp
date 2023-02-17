// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_ActionSocketWeapon.h"
#include "WeaponAction/WeaponAction.h"

void ATest_ActionSocketWeapon::Attack()
{
	if (!AttackAction || !AttackAction->IsValidLowLevel())
		return;

	AttackAction->RunAction(true);
}

void ATest_ActionSocketWeapon::StopAttacking()
{
	if (!AttackAction || !AttackAction->IsValidLowLevel())
		return;

	AttackAction->RunAction(false);
}

void ATest_ActionSocketWeapon::Reload()
{
	if (!ReloadAction || !ReloadAction->IsValidLowLevel())
		return;

	ReloadAction->RunAction(true);
}

void ATest_ActionSocketWeapon::SniperZoom(bool Toggle)
{
	if (!SniperZoomAction || !SniperZoomAction->IsValidLowLevel())
		return;

	SniperZoomAction->RunAction(Toggle);
}
