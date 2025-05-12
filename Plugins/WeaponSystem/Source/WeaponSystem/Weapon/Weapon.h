// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "WeaponBase.h"
#include "Weapon.generated.h"

/**
 * 
 */

class UAbilitySystemComponent;

UCLASS()
class WEAPONSYSTEM_API AWeapon : public AWeaponBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void ResetWeapon(const FWeaponData& InWeaponData) override;

	virtual void Attack() override;
	virtual void Reload() override;
	virtual void StopAttacking() override;

	/** Returns AbilitySystemComponent subobject **/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	FGameplayAbilitySpec AttackAbilitySpec;
	FGameplayAbilitySpec ReloadAbilitySpec;
};
