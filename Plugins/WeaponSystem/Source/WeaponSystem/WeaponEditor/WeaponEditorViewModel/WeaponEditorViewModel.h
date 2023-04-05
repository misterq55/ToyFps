// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WeaponEditorViewModelObject.h"
#include "WeaponEditorViewModel.generated.h"

/**
 * 
 */

UCLASS()
class WEAPONSYSTEM_API UWeaponEditorViewModel : public UObject
{
	GENERATED_BODY()
	
public:
	void SetEditorWorld(UWorld* InEditorWorld) { EditorWorld = InEditorWorld; }
	bool InitializeViewModel(const TArray<UObject*>& InObjects);

	TObjectPtr<class AEditorCharacter> GetEditorCharacter() {
		return EditorCharacter;
	}

	TSharedPtr<FViewModelAssetObject> GetViewModelAssetObject(const FString& InKey);
	TSharedPtr<FViewModelAbilityObject> GetViewModelAbilityObject(const FString& InKey);

	TSharedPtr<FViewModelCrossHairObject> GetViewModelCrossHairObject() {
		return ViewModelCrossHairObject;
	}

private:
	UWorld* EditorWorld = nullptr;
	TObjectPtr<class AEditorCharacter> EditorCharacter = nullptr;

	TMap<FString, TSharedPtr<FViewModelAssetObject>> ViewModelAssetObject;
	TMap<FString, TSharedPtr<FViewModelAbilityObject>> ViewModelAbilityObject;

	TObjectPtr<class UWeaponAsset> CurrentWeaponAsset;
	TSharedPtr<FViewModelCrossHairObject> ViewModelCrossHairObject;
};
