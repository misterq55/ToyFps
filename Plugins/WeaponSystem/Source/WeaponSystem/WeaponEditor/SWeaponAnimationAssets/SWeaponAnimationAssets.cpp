#include "SWeaponAnimationAssets.h"
#include "WeaponSystem/WeaponEditor/WeaponEditor.h"

void SWeaponAnimationAssets::Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor)
{
	WeaponEditor = InSpriteEditor;
}