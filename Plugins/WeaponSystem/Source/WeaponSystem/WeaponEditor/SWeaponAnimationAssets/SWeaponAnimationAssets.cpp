#include "SWeaponAnimationAssets.h"
#include "WeaponSystem/WeaponEditor/WeaponEditor.h"
#include "WeaponSystem/WeaponEditor/WeaponEditorViewModel/WeaponEditorViewModel.h"
#include "PropertyCustomizationHelpers.h"

#include "Animation/BlendSpace.h"
#include "Animation/AnimSequenceBase.h"

void SWeaponAnimationAssets::Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor)
{
	WeaponEditor = InSpriteEditor;

	AssetThumbnailPool = MakeShareable(new FAssetThumbnailPool(1024));

	ChildSlot
		[
			SNew(SVerticalBox)
			// Idle BlendSpace
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Left)
			[
				SNew(SObjectPropertyEntryBox)
				.DisplayBrowse(true)
				.DisplayThumbnail(true)
				.AllowedClass(UBlendSpace::StaticClass())
				.EnableContentPicker(true)
				.ThumbnailPool(AssetThumbnailPool)
				// .ObjectPath(WeaponEditor.Pin()->GetViewModel()->GetIdlePath())
				.ObjectPath_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::GetIdlePath)
				/*.ObjectPath_Lambda([this]()
				{
					return TempPath;
				})
				.OnObjectChanged_Lambda([this](const FAssetData& AssetData)
				{
						TempPath = AssetData.GetObjectPathString();
				})*/
				.OnObjectChanged(FOnSetObject::CreateUObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::OnChangeIdleAsset))
			]

			// Idle ADS BlendSpace
			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Left)
				[
					SNew(SObjectPropertyEntryBox)
					.DisplayBrowse(true)
					.DisplayThumbnail(true)
					.AllowedClass(UAnimSequenceBase::StaticClass())
					.EnableContentPicker(true)
					.ThumbnailPool(AssetThumbnailPool)
					.ObjectPath_Lambda([this]()
					{
						return TempPath2;
					})
					.OnObjectChanged_Lambda([this](const FAssetData& AssetData)
					{
						TempPath2 = AssetData.GetObjectPathString();
					})
				]
		];
}