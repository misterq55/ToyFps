// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToyFpsCharacter.h"
#include "ToyFpsCharacterWithWeaponAsset.generated.h"

/**
 * 
 */

class UWeaponAsset;

UCLASS()
class TOYFPS_API AToyFpsCharacterWithWeaponAsset : public AToyFpsCharacter
{
	GENERATED_BODY()
	
public:
	AToyFpsCharacterWithWeaponAsset();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayName = "Weapon"))
		TObjectPtr<USceneComponent> WeaponPivot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UWeaponAsset> WeaponAsset;
};
