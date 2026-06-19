#include "WeaponEditorModule.h"

#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "WeaponAssetAction/WeaponAssetAction.h"

void FWeaponEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	const TSharedPtr<FWeaponAssetAction> Action = MakeShared<FWeaponAssetAction>();
	AssetTools.RegisterAssetTypeActions(Action.ToSharedRef());
	RegisteredAssetTypeActions.Add(Action);
}

void FWeaponEditorModule::ShutdownModule()
{
	if (!FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		return;
	}

	IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
	for (const TSharedPtr<IAssetTypeActions>& Action : RegisteredAssetTypeActions)
	{
		if (Action.IsValid())
		{
			AssetTools.UnregisterAssetTypeActions(Action.ToSharedRef());
		}
	}
	RegisteredAssetTypeActions.Empty();
}

IMPLEMENT_MODULE(FWeaponEditorModule, WeaponEditor)
