// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "WeaponBase.h"
#include "WeaponWithAbilities.generated.h"

/**
 * 
 */

class UAbilitySystemComponent;

UCLASS()
class WEAPONSYSTEM_API AWeaponWithAbilities : public AWeaponBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AWeaponWithAbilities();

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
