// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToyFpsCharacter.h"
#include "ToyFpsCharacterWithWeaponBP.generated.h"

/**
 * 
 */

class UChildActorComponent;

UCLASS()
class TOYFPS_API AToyFpsCharacterWithWeaponBP : public AToyFpsCharacter
{
	GENERATED_BODY()
	
public:
	AToyFpsCharacterWithWeaponBP();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UChildActorComponent> CurrentWeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AWeaponBase> CurrentWeaponClass;
};
