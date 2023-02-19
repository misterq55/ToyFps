#include "WeaponAssetAction.h"
#include "ToyFPS/Weapon/Weapon.h"
#include "ToyFps/Editor/WeaponEditor/WeaponEditor.h"

FText FWeaponAssetAction::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_Weapon", "Weapon Asset");
}

UClass* FWeaponAssetAction::GetSupportedClass() const
{
	return AWeapon::StaticClass();
}

uint32 FWeaponAssetAction::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

FColor FWeaponAssetAction::GetTypeColor() const
{
	return FColor::Red;
}

void FWeaponAssetAction::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	MakeShared<FWeaponEditor>()->InitEditor(InObjects);
}
