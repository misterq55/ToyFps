// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "AbilitySystemInterface.h"
#include "WeaponWithAbilities.generated.h"

/**
 * 
 */

class UAbilitySystemComponent;

UCLASS()
class TOYFPS_API AWeaponWithAbilities : public AWeapon//, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AWeaponWithAbilities();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Attack();
	/** Returns AbilitySystemComponent subobject **/
	// virtual UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }

private:
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};
