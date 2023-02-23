// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

/**
 * 
 */

class IDetailsView;

class WEAPONSYSTEM_API FWeaponEditor : public FAssetEditorToolkit
{
public:
	void InitEditor(const TArray<UObject*>& InObjects);
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;

	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

protected:
	void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager);
	void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager);
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);

private:
	TSharedPtr<IDetailsView> DetailsView;
};
