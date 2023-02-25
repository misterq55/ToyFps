#include "WeaponAssetAction.h"
#include "WeaponSystem/Weapon/WeaponAsset.h"
#include "WeaponSystem/WeaponEditor/WeaponEditor.h"


FText FWeaponAssetAction::GetName() const
{
	return INVTEXT("Weapon");
}

UClass* FWeaponAssetAction::GetSupportedClass() const
{
	return UWeaponAsset::StaticClass();
}

uint32 FWeaponAssetAction::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

FColor FWeaponAssetAction::GetTypeColor() const
{
	return FColor(0, 141, 98);
}

void FWeaponAssetAction::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	MakeShared<FWeaponEditor>()->InitEditor(InObjects);
}


