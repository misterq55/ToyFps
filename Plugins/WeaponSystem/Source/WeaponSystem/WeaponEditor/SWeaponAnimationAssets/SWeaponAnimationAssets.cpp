#include "SWeaponAnimationAssets.h"
#include "WeaponSystem/WeaponEditor/WeaponEditor.h"
#include "WeaponSystem/WeaponEditor/WeaponEditorViewModel/WeaponEditorViewModel.h"
#include "WeaponSystem/WeaponEditor/SWeaponEditorAssetProperty/SWeaponEditorAssetProperty.h"

#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"

#include "Animation/BlendSpace.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimMontage.h"

void SWeaponAnimationAssets::Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor)
{
	WeaponEditor = InSpriteEditor;

	AssetThumbnailPool = MakeShareable(new FAssetThumbnailPool(1024));

	ChildSlot
		[
			SNew(SVerticalBox)
			
			// Weapon Mesh
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Left)
			[
				SNew(SWeaponEditorAssetProperty)
				.ObjectName(FText::FromString(TEXT("Weapon Mesh")))
				.DisplayBrowse(true)
				.DisplayThumbnail(true)
				.AllowedClass(USkeletalMesh::StaticClass())
				.EnableContentPicker(true)
				.ThumbnailPool(AssetThumbnailPool)
				.ObjectPath(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("WeaponMesh")).ToSharedRef(), &FViewModelAssetObject::GetAssetPath)
				.OnObjectChanged(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("WeaponMesh")).ToSharedRef(), &FViewModelAssetObject::OnChangeAsset)
			]

			// Weapon Mesh
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Left)
			[
				SNew(SWeaponEditorAssetProperty)
				.ObjectName(FText::FromString(TEXT("Pick UP Weapon Mesh")))
				.DisplayBrowse(true)
				.DisplayThumbnail(true)
				.AllowedClass(UStaticMesh::StaticClass())
				.EnableContentPicker(true)
				.ThumbnailPool(AssetThumbnailPool)
				.ObjectPath(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("WeaponPickUpMeshPath")).ToSharedRef(), &FViewModelAssetObject::GetAssetPath)
				.OnObjectChanged(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("WeaponPickUpMeshPath")).ToSharedRef(), &FViewModelAssetObject::OnChangeAsset)
			]

			// Idle BlendSpace
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Left)
			[
				SNew(SWeaponEditorAssetProperty)
				.ObjectName(FText::FromString(TEXT("Idle")))
				.DisplayBrowse(true)
				.DisplayThumbnail(true)
				.AllowedClass(UBlendSpace::StaticClass())
				.EnableContentPicker(true)
				.ThumbnailPool(AssetThumbnailPool)
				.ObjectPath(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("IdlePath")).ToSharedRef(), &FViewModelAssetObject::GetAssetPath)
				.OnObjectChanged(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("IdlePath")).ToSharedRef(), &FViewModelAssetObject::OnChangeAsset)
			]

			// Idle ADS BlendSpace
			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Left)
				[
					SNew(SWeaponEditorAssetProperty)
					.ObjectName(FText::FromString(TEXT("Ads Idle")))
					.DisplayBrowse(true)
					.DisplayThumbnail(true)
					.AllowedClass(UBlendSpace::StaticClass())
					.EnableContentPicker(true)
					.ThumbnailPool(AssetThumbnailPool)
					.ObjectPath(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("AdsIdlePath")).ToSharedRef(), &FViewModelAssetObject::GetAssetPath)
					.OnObjectChanged(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("AdsIdlePath")).ToSharedRef(), &FViewModelAssetObject::OnChangeAsset)
				]

			// Walk AnimSequence
			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Left)
				[
					SNew(SWeaponEditorAssetProperty)
					.ObjectName(FText::FromString(TEXT("Walk Animation Sequence")))
					.DisplayBrowse(true)
					.DisplayThumbnail(true)
					.AllowedClass(UAnimSequenceBase::StaticClass())
					.EnableContentPicker(true)
					.ThumbnailPool(AssetThumbnailPool)
					.ObjectPath(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("WalkAnimSequencePath")).ToSharedRef(), &FViewModelAssetObject::GetAssetPath)
					.OnObjectChanged(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("WalkAnimSequencePath")).ToSharedRef(), &FViewModelAssetObject::OnChangeAsset)
				]

			// Run AnimSequence
			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Left)
				[
					SNew(SWeaponEditorAssetProperty)
					.ObjectName(FText::FromString(TEXT("Run Animation Sequence")))
					.DisplayBrowse(true)
					.DisplayThumbnail(true)
					.AllowedClass(UAnimSequenceBase::StaticClass())
					.EnableContentPicker(true)
					.ThumbnailPool(AssetThumbnailPool)
					.ObjectPath(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("RunAnimSequencePath")).ToSharedRef(), &FViewModelAssetObject::GetAssetPath)
					.OnObjectChanged(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("RunAnimSequencePath")).ToSharedRef(), &FViewModelAssetObject::OnChangeAsset)
				]

			// Jump1 AnimSequence
			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Left)
				[
					SNew(SWeaponEditorAssetProperty)
					.ObjectName(FText::FromString(TEXT("Run Animation Sequence")))
					.DisplayBrowse(true)
					.DisplayThumbnail(true)
					.AllowedClass(UAnimSequenceBase::StaticClass())
					.EnableContentPicker(true)
					.ThumbnailPool(AssetThumbnailPool)
					.ObjectPath(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("Jump1AnimSequencePath")).ToSharedRef(), &FViewModelAssetObject::GetAssetPath)
					.OnObjectChanged(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("Jump1AnimSequencePath")).ToSharedRef(), &FViewModelAssetObject::OnChangeAsset)
				]

			// Jump2 AnimSequence
			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Left)
				[
					SNew(SWeaponEditorAssetProperty)
					.ObjectName(FText::FromString(TEXT("Run Animation Sequence")))
					.DisplayBrowse(true)
					.DisplayThumbnail(true)
					.AllowedClass(UAnimSequenceBase::StaticClass())
					.EnableContentPicker(true)
					.ThumbnailPool(AssetThumbnailPool)
					.ObjectPath(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("Jump2AnimSequencePath")).ToSharedRef(), &FViewModelAssetObject::GetAssetPath)
					.OnObjectChanged(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("Jump2AnimSequencePath")).ToSharedRef(), &FViewModelAssetObject::OnChangeAsset)
				]

			// Jump3 AnimSequence
			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Left)
				[
					SNew(SWeaponEditorAssetProperty)
					.ObjectName(FText::FromString(TEXT("Run Animation Sequence")))
					.DisplayBrowse(true)
					.DisplayThumbnail(true)
					.AllowedClass(UAnimSequenceBase::StaticClass())
					.EnableContentPicker(true)
					.ThumbnailPool(AssetThumbnailPool)
					.ObjectPath(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("Jump3AnimSequencePath")).ToSharedRef(), &FViewModelAssetObject::GetAssetPath)
					.OnObjectChanged(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("Jump3AnimSequencePath")).ToSharedRef(), &FViewModelAssetObject::OnChangeAsset)
				]

			// Weapon Fire AnimSequence
			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Left)
				[
					SNew(SWeaponEditorAssetProperty)
					.ObjectName(FText::FromString(TEXT("Weapon Fire Animation Montage")))
					.DisplayBrowse(true)
					.DisplayThumbnail(true)
					.AllowedClass(UAnimMontage::StaticClass())
					.EnableContentPicker(true)
					.ThumbnailPool(AssetThumbnailPool)
					.ObjectPath(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("WeaponFireAnimMontage")).ToSharedRef(), &FViewModelAssetObject::GetAssetPath)
					.OnObjectChanged(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("WeaponFireAnimMontage")).ToSharedRef(), &FViewModelAssetObject::OnChangeAsset)
				]

			// Ads Weapon Fire AnimSequence
			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Left)
				[
					SNew(SWeaponEditorAssetProperty)
					.ObjectName(FText::FromString(TEXT("Ads Weapon Fire Animation Montage")))
					.DisplayBrowse(true)
					.DisplayThumbnail(true)
					.AllowedClass(UAnimMontage::StaticClass())
					.EnableContentPicker(true)
					.ThumbnailPool(AssetThumbnailPool)
					.ObjectPath(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("AdsWeaponFireAnimMontage")).ToSharedRef(), &FViewModelAssetObject::GetAssetPath)
					.OnObjectChanged(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("AdsWeaponFireAnimMontage")).ToSharedRef(), &FViewModelAssetObject::OnChangeAsset)
				]

			// Weapon Reload AnimSequence
			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Left)
				[
					SNew(SWeaponEditorAssetProperty)
					.ObjectName(FText::FromString(TEXT("Weapon Reload Animation Montage")))
					.DisplayBrowse(true)
					.DisplayThumbnail(true)
					.AllowedClass(UAnimMontage::StaticClass())
					.EnableContentPicker(true)
					.ThumbnailPool(AssetThumbnailPool)
					.ObjectPath(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("WeaponReloadAnimMontage")).ToSharedRef(), &FViewModelAssetObject::GetAssetPath)
					.OnObjectChanged(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("WeaponReloadAnimMontage")).ToSharedRef(), &FViewModelAssetObject::OnChangeAsset)
				]

			// Ads Weapon Reload AnimSequence
			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Left)
				[
					SNew(SWeaponEditorAssetProperty)
					.ObjectName(FText::FromString(TEXT("Ads Weapon Reload Animation Montage")))
					.DisplayBrowse(true)
					.DisplayThumbnail(true)
					.AllowedClass(UAnimMontage::StaticClass())
					.EnableContentPicker(true)
					.ThumbnailPool(AssetThumbnailPool)
					.ObjectPath(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("AdsWeaponReloadAnimMontage")).ToSharedRef(), &FViewModelAssetObject::GetAssetPath)
					.OnObjectChanged(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("AdsWeaponReloadAnimMontage")).ToSharedRef(), &FViewModelAssetObject::OnChangeAsset)
				]

			// Weapon Reload AnimSequence
			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Left)
				[
					SNew(SWeaponEditorAssetProperty)
					.ObjectName(FText::FromString(TEXT("Empty Weapon Reload Animation Montage")))
					.DisplayBrowse(true)
					.DisplayThumbnail(true)
					.AllowedClass(UAnimMontage::StaticClass())
					.EnableContentPicker(true)
					.ThumbnailPool(AssetThumbnailPool)
					.ObjectPath(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("EmptyWeaponReloadAnimMontage")).ToSharedRef(), &FViewModelAssetObject::GetAssetPath)
					.OnObjectChanged(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("EmptyWeaponReloadAnimMontage")).ToSharedRef(), &FViewModelAssetObject::OnChangeAsset)
				]

			// Weapon Reload AnimSequence
			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Left)
				[
					SNew(SWeaponEditorAssetProperty)
					.ObjectName(FText::FromString(TEXT("Ads Empty Weapon Reload Animation Montage")))
					.DisplayBrowse(true)
					.DisplayThumbnail(true)
					.AllowedClass(UAnimMontage::StaticClass())
					.EnableContentPicker(true)
					.ThumbnailPool(AssetThumbnailPool)
					.ObjectPath(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("AdsEmptyWeaponReloadAnimMontage")).ToSharedRef(), &FViewModelAssetObject::GetAssetPath)
					.OnObjectChanged(WeaponEditor.Pin()->GetViewModel()->GetViewModelAssetObject(TEXT("AdsEmptyWeaponReloadAnimMontage")).ToSharedRef(), &FViewModelAssetObject::OnChangeAsset)
				]
		];
}