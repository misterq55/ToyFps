#include "SWeaponAbilities.h"
#include "WeaponSystem/WeaponEditor/WeaponEditor.h"

void SWeaponAbilities::Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor)
{
	WeaponEditor = InSpriteEditor;
}