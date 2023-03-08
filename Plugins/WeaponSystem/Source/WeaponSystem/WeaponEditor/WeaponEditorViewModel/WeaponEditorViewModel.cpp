// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponEditorViewModel.h"
#include "WeaponSystem/Weapon/WeaponAsset.h"
#include "WeaponSystem/Character/EditorCharacter.h"
#include "Animation/BlendSpace.h"
#include "Animation/AnimSequenceBase.h"

bool UWeaponEditorViewModel::InitializeViewModel(const TArray<UObject*>& InObjects)
{
	if (EditorWorld == nullptr)
		return false;

	CurrentWeaponAsset = Cast<UWeaponAsset>(InObjects[0]);
	if (!CurrentWeaponAsset)
		return false;

	EditorCharacter = EditorWorld->SpawnActor<AEditorCharacter>();
	EditorCharacter->SetWeaponAsset(CurrentWeaponAsset);
	EditorCharacter->SpawnWeaponActor();

	return true;
}

void UWeaponEditorViewModel::OnChangeIdleAsset(const FAssetData& AssetData)
{
	if (!CurrentWeaponAsset)
		return;

	SetIdlePath(AssetData.GetObjectPathString());
	FWeaponData& WeaponData = CurrentWeaponAsset->GetWeaponData();
	// CurrentWeaponAsset->GetWeaponData().BlendSpace_WeaponIdle = Cast<UBlendSpace>(AssetData.GetAsset());
	WeaponData.BlendSpace_WeaponIdle = Cast<UBlendSpace>(AssetData.GetAsset());
	EditorCharacter->ResetArmsAnimInstance();
}

void UWeaponEditorViewModel::OnChangeAdsIdleAsset(const FAssetData& AssetData)
{
	if (!CurrentWeaponAsset)
		return;

	SetAdsIdlePath(AssetData.GetObjectPathString());
	CurrentWeaponAsset->GetWeaponData().BlendSpace_WeaponAdsIdle = Cast<UBlendSpace>(AssetData.GetAsset());
	EditorCharacter->ResetArmsAnimInstance();
}
