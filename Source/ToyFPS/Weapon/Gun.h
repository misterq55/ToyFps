// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Gun.generated.h"

/**
 * 
 */
UCLASS()
class TOYFPS_API AGun : public AWeapon
{
	GENERATED_BODY()
	
public:
	AGun();

protected:
	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayName = Muzzle))
		TObjectPtr<USceneComponent> Muzzle;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayName = Eject))
		TObjectPtr<USceneComponent> Eject;
};
