#include "SWeaponInfo.h"
#include "WeaponSystem/WeaponEditor/WeaponEditor.h"

void SWeaponInfo::Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor)
{
	WeaponEditor = InSpriteEditor;
}