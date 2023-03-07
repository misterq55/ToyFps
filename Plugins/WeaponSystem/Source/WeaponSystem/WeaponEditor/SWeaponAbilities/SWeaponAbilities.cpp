#include "SWeaponAbilities.h"
#include "WeaponSystem/WeaponEditor/WeaponEditor.h"
#include "PropertyCustomizationHelpers.h"

#include "WeaponSystem/Weapon/WeaponAbility/WeaponAbility.h"

void SWeaponAbilities::Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor)
{
	WeaponEditor = InSpriteEditor;
	
	AssetThumbnailPool = MakeShareable(new FAssetThumbnailPool(1024));

	ChildSlot
		[
			SNew(SClassPropertyEntryBox)
			.MetaClass(UWeaponAbility::StaticClass())
		.SelectedClass_Lambda([this]()
			{
				return TempClass.Get();
			})
		.OnSetClass_Lambda([this](const UClass* SelectedClass)
			{
				TempClass = MakeWeakObjectPtr(SelectedClass);
			})
		];
}