// Fill out your copyright notice in the Description page of Project Settings.


#include "BluprintWeaponAction.h"

UBluprintWeaponAction::UBluprintWeaponAction()
{
}

void UBluprintWeaponAction::RunAction(bool bStart)
{
	RunAction_Blueprint(bStart);
}

void UBluprintWeaponAction::RunAction_Blueprint_Implementation(bool bStart)
{
}
