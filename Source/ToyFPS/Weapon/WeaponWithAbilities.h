// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponWithAbilities.generated.h"

/**
 * 
 */
UCLASS()
class TOYFPS_API AWeaponWithAbilities : public AWeapon
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Attack();
};
