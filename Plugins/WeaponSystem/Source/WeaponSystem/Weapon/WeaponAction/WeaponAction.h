// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponAction.generated.h"

/**
 * 
 */

UCLASS(BlueprintType, Blueprintable)
class WEAPONSYSTEM_API UWeaponAction : public UObject, public IInterface_AssetUserData
{
	GENERATED_BODY()

public:
	UWeaponAction();

public:
	UFUNCTION(BlueprintCallable, Category = Weapon)
		virtual void RunAction(bool bStart) {}
};
