// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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

	FString GetIdlePath() const { 
		return IdlePath; 
	}
	void SetIdlePath(FString InIdlePath) { IdlePath = InIdlePath; }
	void OnChangeIdleAsset(const FAssetData& AssetData);

	FString GetAdsIdlePath() const { return AdsIdlePath; }
	void SetAdsIdlePath(FString InAdsIdlePath) { AdsIdlePath = InAdsIdlePath; }
	void OnChangeAdsIdleAsset(const FAssetData& AssetData);

private:
	UWorld* EditorWorld = nullptr;
	TObjectPtr<class AEditorCharacter> EditorCharacter = nullptr;
	FString IdlePath;
	FString AdsIdlePath;
	TObjectPtr<class UWeaponAsset> CurrentWeaponAsset;
};
