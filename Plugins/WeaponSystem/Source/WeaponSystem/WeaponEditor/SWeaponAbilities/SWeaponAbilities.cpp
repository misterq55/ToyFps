#include "SWeaponAbilities.h"
#include "WeaponSystem/WeaponEditor/WeaponEditor.h"
#include "WeaponSystem/WeaponEditor/WeaponEditorViewModel/WeaponEditorViewModel.h"
#include "WeaponSystem/WeaponEditor/SWeaponEditorClassProperty/SWeaponEditorClassProperty.h"

#include "WeaponSystem/Weapon/WeaponAbility/WeaponAbility.h"

void SWeaponAbilities::Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor)
{
	WeaponEditor = InSpriteEditor;
	
	AssetThumbnailPool = MakeShareable(new FAssetThumbnailPool(1024));

	ChildSlot
		[
			SNew(SWeaponEditorClassProperty)
			.ClassName(FText::FromString(TEXT("Attack Ability")))
		.MetaClass(UWeaponAbility::StaticClass())
		.SelectedClass_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::OnGetClass)
		.OnSetClass_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::OnSetClass)
		.OnClicked_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::ClickedOnRunAttackAbility)
		];
}