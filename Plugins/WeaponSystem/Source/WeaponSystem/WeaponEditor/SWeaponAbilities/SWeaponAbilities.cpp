#include "SWeaponAbilities.h"
#include "WeaponSystem/WeaponEditor/WeaponEditor.h"
#include "WeaponSystem/WeaponEditor/WeaponEditorViewModel/WeaponEditorViewModel.h"
#include "WeaponSystem/WeaponEditor/SWeaponEditorClassProperty/SWeaponEditorClassProperty.h"

#include "WeaponSystem/Weapon/WeaponAbility/WeaponAbility.h"

void SWeaponAbilities::Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor)
{
	WeaponEditor = InSpriteEditor;
	
	ChildSlot
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SWeaponEditorClassProperty)
				.ClassName(FText::FromString(TEXT("Attack Ability")))
				.MetaClass(UWeaponAbility::StaticClass())
				.SelectedClass_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::OnGetAttackAbilityClass)
				.OnSetClass_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::OnSetAttackAbilityClass)
				.OnClicked_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::ClickedOnRunAttackAbility)
			]

			+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SWeaponEditorClassProperty)
					.ClassName(FText::FromString(TEXT("Reload Ability")))
				.MetaClass(UWeaponAbility::StaticClass())
				.SelectedClass_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::OnGetReloadAbilityClass)
				.OnSetClass_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::OnSetReloadAbilityClass)
				.OnClicked_UObject(WeaponEditor.Pin()->GetViewModel(), &UWeaponEditorViewModel::ClickedOnRunReloadAbility)
				]
		];
}