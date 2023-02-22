// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponAction.h"
#include "BluprintWeaponAction.generated.h"

/**
 * 
 */

UCLASS(BlueprintType, Blueprintable)
class WEAPONSYSTEM_API UBluprintWeaponAction : public UWeaponAction
{
	GENERATED_BODY()

public:
	UBluprintWeaponAction();

	virtual void RunAction(bool bStart) override;

	UFUNCTION(BlueprintNativeEvent, Category = WeaponAction)
		void RunAction_Blueprint(bool bStart);
};
