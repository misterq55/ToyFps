// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponSystem/WeaponSystemDefine.h"
#include "WeaponAsset.generated.h"

/**
 * 
 */
UCLASS()
class WEAPONSYSTEM_API UWeaponAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	FWeaponData& GetWeaponData() {
		return WeaponData;
	}
protected:
	UPROPERTY(EditDefaultsOnly)
	FWeaponData WeaponData;
};
