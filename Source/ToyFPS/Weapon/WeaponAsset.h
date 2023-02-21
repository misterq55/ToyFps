// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ToyFPS/ToyFpsDefine.h"
#include "WeaponAsset.generated.h"

/**
 * 
 */
UCLASS()
class TOYFPS_API UWeaponAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	FWeaponData& GetWeaponData() {
		return WeaponData;
	}
protected:
	FWeaponData WeaponData;
};
