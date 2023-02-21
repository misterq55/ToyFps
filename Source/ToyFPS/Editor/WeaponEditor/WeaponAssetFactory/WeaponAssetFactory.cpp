// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAssetFactory.h"
#include "ToyFPS/Weapon/WeaponAsset.h"

UWeaponAssetFactory::UWeaponAssetFactory(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SupportedClass = UWeaponAsset::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UWeaponAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UWeaponAsset>(InParent, InClass, InName, Flags);;
}

bool UWeaponAssetFactory::ShouldShowInNewMenu() const
{
	return false;
}
