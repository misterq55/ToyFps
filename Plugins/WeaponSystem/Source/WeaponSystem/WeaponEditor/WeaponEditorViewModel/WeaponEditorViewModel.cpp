// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponEditorViewModel.h"
#include "WeaponSystem/Weapon/WeaponAsset.h"
#include "WeaponSystem/Character/EditorCharacter.h"
#include "WeaponSystem/Weapon/WeaponBase.h"
#include "Animation/BlendSpace.h"
#include "Animation/AnimSequenceBase.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"

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

	SetWeaponMeshPath(CurrentWeaponAsset->GetWeaponData().WeaponMesh->GetPathName());
	SetWeaponPickUpMeshPath(CurrentWeaponAsset->GetWeaponData().WeaponPickUpMesh->GetPathName());
	SetIdlePath(CurrentWeaponAsset->GetWeaponData().BlendSpace_WeaponIdle->GetPathName());
	SetAdsIdlePath(CurrentWeaponAsset->GetWeaponData().BlendSpace_WeaponAdsIdle->GetPathName());
	SetWalkAnimSequencePath(CurrentWeaponAsset->GetWeaponData().AnimSequence_WeaponWalk->GetPathName());
	SetRunAnimSequencePath(CurrentWeaponAsset->GetWeaponData().AnimSequence_WeaponRun->GetPathName());
	SetJump1AnimSequencePath(CurrentWeaponAsset->GetWeaponData().AnimSequence_WeoponJumpSequence1->GetPathName());
	SetJump2AnimSequencePath(CurrentWeaponAsset->GetWeaponData().AnimSequence_WeoponJumpSequence2->GetPathName());
	SetJump3AnimSequencePath(CurrentWeaponAsset->GetWeaponData().AnimSequence_WeoponJumpSequence3->GetPathName());

	AttackAbilityClass = MakeWeakObjectPtr(CurrentWeaponAsset->GetWeaponData().AttackAbility->GetOwnerClass());
	ReloadAbilityClass = MakeWeakObjectPtr(CurrentWeaponAsset->GetWeaponData().ReloadAbility->GetOwnerClass());

	return true;
}

void UWeaponEditorViewModel::OnChangeWeaponMeshAsset(const FAssetData& AssetData)
{
	if (!CurrentWeaponAsset)
		return;

	SetWeaponMeshPath(AssetData.GetObjectPathString());
	CurrentWeaponAsset->GetWeaponData().WeaponMesh = Cast<USkeletalMesh>(AssetData.GetAsset());
	EditorCharacter->ResetWeaponData(CurrentWeaponAsset->GetWeaponData());
}

void UWeaponEditorViewModel::OnChangeWeaponPickUpMeshAsset(const FAssetData& AssetData)
{
	if (!CurrentWeaponAsset)
		return;

	SetWeaponPickUpMeshPath(AssetData.GetObjectPathString());
	CurrentWeaponAsset->GetWeaponData().WeaponPickUpMesh = Cast<UStaticMesh>(AssetData.GetAsset());;
	EditorCharacter->ResetWeaponData(CurrentWeaponAsset->GetWeaponData());
}

void UWeaponEditorViewModel::OnChangeIdleAsset(const FAssetData& AssetData)
{
	if (!CurrentWeaponAsset)
		return;

	SetIdlePath(AssetData.GetObjectPathString());
	CurrentWeaponAsset->GetWeaponData().BlendSpace_WeaponIdle = Cast<UBlendSpace>(AssetData.GetAsset());
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

void UWeaponEditorViewModel::OnChangeWalkAnimSequenceAsset(const FAssetData& AssetData)
{
	if (!CurrentWeaponAsset)
		return;

	SetWalkAnimSequencePath(AssetData.GetObjectPathString());
	CurrentWeaponAsset->GetWeaponData().AnimSequence_WeaponWalk = Cast<UAnimSequenceBase>(AssetData.GetAsset());
	EditorCharacter->ResetArmsAnimInstance();
}

void UWeaponEditorViewModel::OnChangeRunAnimSequenceAsset(const FAssetData& AssetData)
{
	if (!CurrentWeaponAsset)
		return;

	SetRunAnimSequencePath(AssetData.GetObjectPathString());
	CurrentWeaponAsset->GetWeaponData().AnimSequence_WeaponRun = Cast<UAnimSequenceBase>(AssetData.GetAsset());
	EditorCharacter->ResetArmsAnimInstance();
}

void UWeaponEditorViewModel::OnChangeJump1AnimSequenceAsset(const FAssetData& AssetData)
{
	if (!CurrentWeaponAsset)
		return;

	SetJump1AnimSequencePath(AssetData.GetObjectPathString());
	CurrentWeaponAsset->GetWeaponData().AnimSequence_WeoponJumpSequence1 = Cast<UAnimSequenceBase>(AssetData.GetAsset());
	EditorCharacter->ResetArmsAnimInstance();
}

void UWeaponEditorViewModel::OnChangeJump2AnimSequenceAsset(const FAssetData& AssetData)
{
	if (!CurrentWeaponAsset)
		return;

	SetJump2AnimSequencePath(AssetData.GetObjectPathString());
	CurrentWeaponAsset->GetWeaponData().AnimSequence_WeoponJumpSequence2 = Cast<UAnimSequenceBase>(AssetData.GetAsset());
	EditorCharacter->ResetArmsAnimInstance();
}

void UWeaponEditorViewModel::OnChangeJump3AnimSequenceAsset(const FAssetData& AssetData)
{
	if (!CurrentWeaponAsset)
		return;

	SetJump3AnimSequencePath(AssetData.GetObjectPathString());
	CurrentWeaponAsset->GetWeaponData().AnimSequence_WeoponJumpSequence3 = Cast<UAnimSequenceBase>(AssetData.GetAsset());
	EditorCharacter->ResetArmsAnimInstance();
}

FReply UWeaponEditorViewModel::ClickedOnRunAttackAbility()
{
	if (!EditorCharacter)
		return FReply::Handled();
		
	EditorCharacter->GetCurrentWeapon()->Attack();

	return FReply::Handled();
}

FReply UWeaponEditorViewModel::ClickedOnRunReloadAbility()
{
	if (!EditorCharacter)
		return FReply::Handled();

	EditorCharacter->GetCurrentWeapon()->Reload();

	return FReply::Handled();
}
