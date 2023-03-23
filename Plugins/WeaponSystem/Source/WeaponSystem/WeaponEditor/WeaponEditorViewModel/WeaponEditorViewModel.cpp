// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponEditorViewModel.h"
#include "WeaponSystem/Weapon/WeaponAsset.h"
#include "WeaponSystem/Character/EditorCharacter.h"
#include "WeaponSystem/Weapon/WeaponBase.h"
#include "Animation/BlendSpace.h"
#include "Animation/AnimSequenceBase.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"
#include "WeaponSystem/WeaponEditor/SWeaponCrossHair/SWeaponCrossHair.h"

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

	ViewModelAssetObject.Add(TEXT("WeaponMesh"), MakeShareable(new FViewModelAssetObject(CurrentWeaponAsset->GetWeaponData().WeaponMesh->GetPathName(),
		[&](const FAssetData& AssetData) {
			if (!CurrentWeaponAsset)
				return;

			CurrentWeaponAsset->GetWeaponData().WeaponMesh = Cast<USkeletalMesh>(AssetData.GetAsset());
			EditorCharacter->ResetWeaponData(CurrentWeaponAsset->GetWeaponData());
		}
		)));

	ViewModelAssetObject.Add(TEXT("WeaponPickUpMeshPath"), MakeShareable(new FViewModelAssetObject(CurrentWeaponAsset->GetWeaponData().WeaponPickUpMesh->GetPathName(),
		[&](const FAssetData& AssetData) {
			if (!CurrentWeaponAsset)
				return;

			CurrentWeaponAsset->GetWeaponData().WeaponPickUpMesh = Cast<UStaticMesh>(AssetData.GetAsset());;
			EditorCharacter->ResetWeaponData(CurrentWeaponAsset->GetWeaponData());
		}
	)));

	ViewModelAssetObject.Add(TEXT("IdlePath"), MakeShareable(new FViewModelAssetObject(CurrentWeaponAsset->GetWeaponData().BlendSpace_WeaponIdle->GetPathName(),
		[&](const FAssetData& AssetData) {
			if (!CurrentWeaponAsset)
				return;

			CurrentWeaponAsset->GetWeaponData().BlendSpace_WeaponIdle = Cast<UBlendSpace>(AssetData.GetAsset());
			EditorCharacter->ResetArmsAnimInstance();
		}
	)));

	ViewModelAssetObject.Add(TEXT("AdsIdlePath"), MakeShareable(new FViewModelAssetObject(CurrentWeaponAsset->GetWeaponData().BlendSpace_WeaponAdsIdle->GetPathName(),
		[&](const FAssetData& AssetData) {
			if (!CurrentWeaponAsset)
				return;

			CurrentWeaponAsset->GetWeaponData().BlendSpace_WeaponAdsIdle = Cast<UBlendSpace>(AssetData.GetAsset());
			EditorCharacter->ResetArmsAnimInstance();
		}
	)));

	ViewModelAssetObject.Add(TEXT("WalkAnimSequencePath"), MakeShareable(new FViewModelAssetObject(CurrentWeaponAsset->GetWeaponData().AnimSequence_WeaponWalk->GetPathName(),
		[&](const FAssetData& AssetData) {
			if (!CurrentWeaponAsset)
				return;

			CurrentWeaponAsset->GetWeaponData().AnimSequence_WeaponWalk = Cast<UAnimSequenceBase>(AssetData.GetAsset());
			EditorCharacter->ResetArmsAnimInstance();
		}
	)));

	ViewModelAssetObject.Add(TEXT("RunAnimSequencePath"), MakeShareable(new FViewModelAssetObject(CurrentWeaponAsset->GetWeaponData().AnimSequence_WeaponRun->GetPathName(),
		[&](const FAssetData& AssetData) {
			if (!CurrentWeaponAsset)
				return;

			CurrentWeaponAsset->GetWeaponData().AnimSequence_WeaponRun = Cast<UAnimSequenceBase>(AssetData.GetAsset());
			EditorCharacter->ResetArmsAnimInstance();
		}
	)));

	ViewModelAssetObject.Add(TEXT("Jump1AnimSequencePath"), MakeShareable(new FViewModelAssetObject(CurrentWeaponAsset->GetWeaponData().AnimSequence_WeoponJumpSequence1->GetPathName(),
		[&](const FAssetData& AssetData) {
			if (!CurrentWeaponAsset)
				return;

			CurrentWeaponAsset->GetWeaponData().AnimSequence_WeoponJumpSequence1 = Cast<UAnimSequenceBase>(AssetData.GetAsset());
			EditorCharacter->ResetArmsAnimInstance();
		}
	)));

	ViewModelAssetObject.Add(TEXT("Jump2AnimSequencePath"), MakeShareable(new FViewModelAssetObject(CurrentWeaponAsset->GetWeaponData().AnimSequence_WeoponJumpSequence2->GetPathName(),
		[&](const FAssetData& AssetData) {
			if (!CurrentWeaponAsset)
				return;

			CurrentWeaponAsset->GetWeaponData().AnimSequence_WeoponJumpSequence2 = Cast<UAnimSequenceBase>(AssetData.GetAsset());
			EditorCharacter->ResetArmsAnimInstance();
		}
	)));


	ViewModelAssetObject.Add(TEXT("Jump3AnimSequencePath"), MakeShareable(new FViewModelAssetObject(CurrentWeaponAsset->GetWeaponData().AnimSequence_WeoponJumpSequence3->GetPathName(),
		[&](const FAssetData& AssetData) {
			if (!CurrentWeaponAsset)
				return;

			CurrentWeaponAsset->GetWeaponData().AnimSequence_WeoponJumpSequence3 = Cast<UAnimSequenceBase>(AssetData.GetAsset());
			EditorCharacter->ResetArmsAnimInstance();
		}
	)));

	ViewModelAssetObject.Add(TEXT("WeaponFireAnimMontage"), MakeShareable(new FViewModelAssetObject(CurrentWeaponAsset->GetWeaponData().AnimMontage_WeaponFire->GetPathName(),
		[&](const FAssetData& AssetData) {
			if (!CurrentWeaponAsset)
				return;

			CurrentWeaponAsset->GetWeaponData().AnimMontage_WeaponFire = Cast<UAnimMontage>(AssetData.GetAsset());
			EditorCharacter->ResetWeaponData(CurrentWeaponAsset->GetWeaponData());
		}
	)));

	ViewModelAssetObject.Add(TEXT("AdsWeaponFireAnimMontage"), MakeShareable(new FViewModelAssetObject(CurrentWeaponAsset->GetWeaponData().AnimMontage_AdsWeaponFire->GetPathName(),
		[&](const FAssetData& AssetData) {
			if (!CurrentWeaponAsset)
				return;

			CurrentWeaponAsset->GetWeaponData().AnimMontage_AdsWeaponFire = Cast<UAnimMontage>(AssetData.GetAsset());
			EditorCharacter->ResetWeaponData(CurrentWeaponAsset->GetWeaponData());
		}
	)));

	ViewModelAssetObject.Add(TEXT("WeaponReloadAnimMontage"), MakeShareable(new FViewModelAssetObject(CurrentWeaponAsset->GetWeaponData().AnimMontage_WeaponReload->GetPathName(),
		[&](const FAssetData& AssetData) {
			if (!CurrentWeaponAsset)
				return;

			CurrentWeaponAsset->GetWeaponData().AnimMontage_WeaponReload = Cast<UAnimMontage>(AssetData.GetAsset());
			EditorCharacter->ResetWeaponData(CurrentWeaponAsset->GetWeaponData());
		}
	)));

	ViewModelAssetObject.Add(TEXT("AdsWeaponReloadAnimMontage"), MakeShareable(new FViewModelAssetObject(CurrentWeaponAsset->GetWeaponData().AnimMontage_AdsWeaponReload->GetPathName(),
		[&](const FAssetData& AssetData) {
			if (!CurrentWeaponAsset)
				return;

			CurrentWeaponAsset->GetWeaponData().AnimMontage_AdsWeaponReload = Cast<UAnimMontage>(AssetData.GetAsset());
			EditorCharacter->ResetWeaponData(CurrentWeaponAsset->GetWeaponData());
		}
	)));

	ViewModelAssetObject.Add(TEXT("EmptyWeaponReloadAnimMontage"), MakeShareable(new FViewModelAssetObject(CurrentWeaponAsset->GetWeaponData().AnimMontage_EmptyWeaponReload->GetPathName(),
		[&](const FAssetData& AssetData) {
			if (!CurrentWeaponAsset)
				return;

			CurrentWeaponAsset->GetWeaponData().AnimMontage_EmptyWeaponReload = Cast<UAnimMontage>(AssetData.GetAsset());
			EditorCharacter->ResetWeaponData(CurrentWeaponAsset->GetWeaponData());
		}
	)));

	ViewModelAssetObject.Add(TEXT("AdsEmptyWeaponReloadAnimMontage"), MakeShareable(new FViewModelAssetObject(CurrentWeaponAsset->GetWeaponData().AnimMontage_AdsEmptyWeaponReload->GetPathName(),
		[&](const FAssetData& AssetData) {
			if (!CurrentWeaponAsset)
				return;

			CurrentWeaponAsset->GetWeaponData().AnimMontage_AdsEmptyWeaponReload = Cast<UAnimMontage>(AssetData.GetAsset());
			EditorCharacter->ResetWeaponData(CurrentWeaponAsset->GetWeaponData());
		}
	)));

	ViewModelAbilityObject.Add(TEXT("CrossHair"), MakeShareable(new FViewModelAbilityObject(CurrentWeaponAsset->GetWeaponData().CrossHair->GetOwnerClass(),
		[&](const UClass* SelectedClass) {
			CurrentWeaponAsset->GetWeaponData().CrossHair = SelectedClass->GetOwnerClass();
		},
		[&]()
		{
			UWeaponCrossHairWidget* CrossHair = CreateWidget<UWeaponCrossHairWidget>(GetWorld(), CurrentWeaponAsset->GetWeaponData().CrossHair);
			/*CrossHair->SetCenterPivot(FVector2D(-4.960938, -12.540527));
			CrossHair->NativeConstruct();
			CrossHair->SetOwningCharacter(EditorCharacter);
			CrossHair->AddToViewport();*/

			// TSharedPtr<SWeaponCrossHair> CrossHairWidget = SNew(SWeaponCrossHair);
			CrossHairWidget.Pin()->SetCrossHairWidget(CrossHair);
		}
	)));

	auto OnSetAttackAbilityClass = [&](const UClass* SelectedClass) {
		CurrentWeaponAsset->GetWeaponData().AttackAbility = SelectedClass->GetOwnerClass();
		EditorCharacter->ResetWeaponData(CurrentWeaponAsset->GetWeaponData());
	};

	auto OnClickAttackAbility = [&]() {
		EditorCharacter->GetCurrentWeapon()->Attack();
	};

	ViewModelAbilityObject.Add(TEXT("Attack"), MakeShareable(new FViewModelAbilityObject(CurrentWeaponAsset->GetWeaponData().AttackAbility->GetOwnerClass(),
		OnSetAttackAbilityClass,
		OnClickAttackAbility
	)));

	auto OnSetReloadAbilityClass = [&](const UClass* SelectedClass) {
		CurrentWeaponAsset->GetWeaponData().ReloadAbility = SelectedClass->GetOwnerClass();
		EditorCharacter->ResetWeaponData(CurrentWeaponAsset->GetWeaponData());
	};

	auto OnClickReloadAbility = [&]() {
		EditorCharacter->GetCurrentWeapon()->Reload();
	};

	ViewModelAbilityObject.Add(TEXT("Reload"), MakeShareable(new FViewModelAbilityObject(CurrentWeaponAsset->GetWeaponData().ReloadAbility->GetOwnerClass(),
		OnSetReloadAbilityClass,
		OnClickReloadAbility
	)));

	return true;
}

TSharedPtr<FViewModelAssetObject> UWeaponEditorViewModel::GetViewModelAssetObject(const FString& InKey)
{
	return ViewModelAssetObject[InKey];
}

TSharedPtr<FViewModelAbilityObject> UWeaponEditorViewModel::GetViewModelAbilityObject(const FString& InKey)
{
	return ViewModelAbilityObject[InKey];
}
