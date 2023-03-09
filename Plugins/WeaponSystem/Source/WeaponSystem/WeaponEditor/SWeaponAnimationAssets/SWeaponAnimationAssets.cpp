#include "SWeaponAnimationAssets.h"
#include "WeaponSystem/WeaponEditor/WeaponEditor.h"
#include "WeaponSystem/WeaponEditor/WeaponEditorViewModel/WeaponEditorViewModel.h"
#include "WeaponSystem/WeaponEditor/SWeaponEditorAssetProperty/SWeaponEditorAssetProperty.h"

#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"

#include "Animation/BlendSpace.h"
#include "Animation/AnimSequenceBase.h"

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
				.ObjectPath_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::GetWeaponMeshPath)
				.OnObjectChanged(FOnSetObject::CreateUObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::OnChangeWeaponMeshAsset))
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
				.ObjectPath_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::GetWeaponPickUpMeshPath)
				.OnObjectChanged(FOnSetObject::CreateUObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::OnChangeWeaponPickUpMeshAsset))
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
				.ObjectPath_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::GetIdlePath)
				.OnObjectChanged(FOnSetObject::CreateUObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::OnChangeIdleAsset))
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
					.ObjectPath_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::GetAdsIdlePath)
					.OnObjectChanged(FOnSetObject::CreateUObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::OnChangeAdsIdleAsset))
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
					.ObjectPath_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::GetWalkAnimSequencePath)
					.OnObjectChanged(FOnSetObject::CreateUObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::OnChangeWalkAnimSequenceAsset))
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
					.ObjectPath_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::GetRunAnimSequencePath)
					.OnObjectChanged(FOnSetObject::CreateUObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::OnChangeRunAnimSequenceAsset))
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
					.ObjectPath_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::GetJump1AnimSequencePath)
					.OnObjectChanged(FOnSetObject::CreateUObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::OnChangeJump1AnimSequenceAsset))
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
					.ObjectPath_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::GetJump2AnimSequencePath)
					.OnObjectChanged(FOnSetObject::CreateUObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::OnChangeJump2AnimSequenceAsset))
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
					.ObjectPath_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::GetJump3AnimSequencePath)
					.OnObjectChanged(FOnSetObject::CreateUObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::OnChangeJump3AnimSequenceAsset))
				]
		];
}