// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FpsCharacterBase.h"
#include "WeaponSystem/WeaponSystemDefine.h"
#include "EditorCharacter.generated.h"

/**
 * 
 */

class UWeaponAsset;

UCLASS()
class WEAPONSYSTEM_API AEditorCharacter : public AFpsCharacterBase
{
	GENERATED_BODY()
	
public:
	AEditorCharacter();
	void SpawnWeaponActor();
	void SetWeaponAsset(UWeaponAsset* InWeaponAsset);
	void ResetArmsAnimInstance();
	void ResetWeaponData(const FWeaponData& InWeaponData);

private:
	TObjectPtr<USceneComponent> WeaponPivot;
	TObjectPtr<UWeaponAsset> WeaponAsset;
};
