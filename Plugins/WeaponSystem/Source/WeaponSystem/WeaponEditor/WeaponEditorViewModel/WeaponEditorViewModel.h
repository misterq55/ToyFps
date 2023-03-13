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

	FString GetWeaponMeshPath() const { return WeaponMeshPath; }
	void SetWeaponMeshPath(FString InWeaponMeshPath) { WeaponMeshPath = InWeaponMeshPath; }
	void OnChangeWeaponMeshAsset(const FAssetData& AssetData);

	FString GetWeaponPickUpMeshPath() const { return WeaponPickUpMeshPath; }
	void SetWeaponPickUpMeshPath(FString InWeaponPickUpMeshPath) { WeaponPickUpMeshPath = InWeaponPickUpMeshPath; }
	void OnChangeWeaponPickUpMeshAsset(const FAssetData& AssetData);

	FString GetIdlePath() const { return IdlePath; }
	void SetIdlePath(FString InIdlePath) { IdlePath = InIdlePath; }
	void OnChangeIdleAsset(const FAssetData& AssetData);

	FString GetAdsIdlePath() const { return AdsIdlePath; }
	void SetAdsIdlePath(FString InAdsIdlePath) { AdsIdlePath = InAdsIdlePath; }
	void OnChangeAdsIdleAsset(const FAssetData& AssetData);

	FString GetWalkAnimSequencePath() const { return WalkAnimSequencePath; }
	void SetWalkAnimSequencePath(FString InWalkAnimSequencePath) { WalkAnimSequencePath = InWalkAnimSequencePath; }
	void OnChangeWalkAnimSequenceAsset(const FAssetData& AssetData);

	FString GetRunAnimSequencePath() const { return RunAnimSequencePath; }
	void SetRunAnimSequencePath(FString InRunAnimSequencePath) { RunAnimSequencePath = InRunAnimSequencePath; }
	void OnChangeRunAnimSequenceAsset(const FAssetData& AssetData);

	FString GetJump1AnimSequencePath() const { return Jump1AnimSequencePath; }
	void SetJump1AnimSequencePath(FString InJump1AnimSequencePath) { Jump1AnimSequencePath = InJump1AnimSequencePath; }
	void OnChangeJump1AnimSequenceAsset(const FAssetData& AssetData);

	FString GetJump2AnimSequencePath() const { return Jump2AnimSequencePath; }
	void SetJump2AnimSequencePath(FString InJump2AnimSequencePath) { Jump2AnimSequencePath = InJump2AnimSequencePath; }
	void OnChangeJump2AnimSequenceAsset(const FAssetData& AssetData);

	FString GetJump3AnimSequencePath() const { return Jump3AnimSequencePath; }
	void SetJump3AnimSequencePath(FString InJump3AnimSequencePath) { Jump3AnimSequencePath = InJump3AnimSequencePath; }
	void OnChangeJump3AnimSequenceAsset(const FAssetData& AssetData);

	const UClass* OnGetAttackAbilityClass() const
	{
		return AttackAbilityClass.Get();
	}

	void OnSetAttackAbilityClass(const UClass* SelectedClass)
	{
		AttackAbilityClass = MakeWeakObjectPtr(SelectedClass);
	}

	FReply ClickedOnRunAttackAbility();

	const UClass* OnGetReloadAbilityClass() const
	{
		return ReloadAbilityClass.Get();
	}

	void OnSetReloadAbilityClass(const UClass* SelectedClass)
	{
		ReloadAbilityClass = MakeWeakObjectPtr(SelectedClass);
	}

	FReply ClickedOnRunReloadAbility();

private:
	UWorld* EditorWorld = nullptr;
	TObjectPtr<class AEditorCharacter> EditorCharacter = nullptr;
	FString WeaponMeshPath;
	FString WeaponPickUpMeshPath;
	FString IdlePath;
	FString AdsIdlePath;
	FString WalkAnimSequencePath;
	FString RunAnimSequencePath;
	FString Jump1AnimSequencePath;
	FString Jump2AnimSequencePath;
	FString Jump3AnimSequencePath;
	TObjectPtr<class UWeaponAsset> CurrentWeaponAsset;
	TWeakObjectPtr<const UClass> AttackAbilityClass;
	TWeakObjectPtr<const UClass> ReloadAbilityClass;
};
