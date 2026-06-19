#include "SWeaponInfo.h"
#include "WeaponEditor.h"
#include "WeaponEditorViewModel/WeaponEditorViewModel.h"

void SWeaponInfo::Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor)
{
	WeaponEditor = InSpriteEditor;
}