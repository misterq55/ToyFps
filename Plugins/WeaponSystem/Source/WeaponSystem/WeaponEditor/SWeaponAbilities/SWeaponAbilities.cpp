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
				.SelectedClass(WeaponEditor.Pin()->GetViewModel()->GetViewModelAbilityObject(TEXT("Attack")).ToSharedRef(), &FViewModelAbilityObject::OnGetAbilityClass)
				.OnSetClass(WeaponEditor.Pin()->GetViewModel()->GetViewModelAbilityObject(TEXT("Attack")).ToSharedRef(), &FViewModelAbilityObject::OnSetAbilityClass)
				.OnClicked(WeaponEditor.Pin()->GetViewModel()->GetViewModelAbilityObject(TEXT("Attack")).ToSharedRef(), &FViewModelAbilityObject::ClickedOnRunAbility)
			]

			+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SWeaponEditorClassProperty)
					.ClassName(FText::FromString(TEXT("Reload Ability")))
				.MetaClass(UWeaponAbility::StaticClass())
				.SelectedClass(WeaponEditor.Pin()->GetViewModel()->GetViewModelAbilityObject(TEXT("Reload")).ToSharedRef(), &FViewModelAbilityObject::OnGetAbilityClass)
				.OnSetClass(WeaponEditor.Pin()->GetViewModel()->GetViewModelAbilityObject(TEXT("Reload")).ToSharedRef(), &FViewModelAbilityObject::OnSetAbilityClass)
				.OnClicked(WeaponEditor.Pin()->GetViewModel()->GetViewModelAbilityObject(TEXT("Reload")).ToSharedRef(), &FViewModelAbilityObject::ClickedOnRunAbility)
				]
		];
}