// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

/**
 * 
 */

class IDetailsView;
class SWeaponEditorViewport;
class SWeaponInfo;
class SWeaponAnimationAssets;
class SWeaponAbilities;
class AEditorCharacter;
class FPreviewScene;
class UWeaponEditorViewModel;
class SWeaponCrossHair;

class WEAPONSYSTEM_API FWeaponEditor : public FAssetEditorToolkit, public FTickableEditorObject
{
public:
	void InitEditor(const TArray<UObject*>& InObjects);
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;

	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	TObjectPtr<AEditorCharacter> GetEditorCharacter();
	UWeaponEditorViewModel* GetViewModel() { return ViewModel; }

	TSharedPtr<SWeaponCrossHair> GetWeaponCrossHair() {
		return CrossHairWidget;
	}

	// FTickableEditorObject Interface
	virtual TStatId GetStatId() const override;
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return true; }
	// End of FTickableEditorObject interface

protected:
	void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager);
	void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager);
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_EditorViewport(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_FirstPersonViewport(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_WeaponInfo(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_AnimationAssets(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_WeaponAbilities(const FSpawnTabArgs& Args);

private:
	TSharedPtr<IDetailsView> DetailsView;
	TSharedPtr<SWeaponEditorViewport> EditorViewport;
	TSharedPtr<SWeaponEditorViewport> FirstPersonViewport;
	TSharedPtr<SWeaponInfo> WeaponInfo;
	TSharedPtr<SWeaponAnimationAssets> WeaponAnimationAssets;
	TSharedPtr<SWeaponAbilities> WeaponAbilities;
	TSharedPtr<FPreviewScene> WeaponEditorPreviewScene;
	UWeaponEditorViewModel* ViewModel;
	TSharedPtr<SWeaponCrossHair> CrossHairWidget;
};
