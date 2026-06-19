#pragma once

#include "Modules/ModuleManager.h"

class FWeaponEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TArray<TSharedPtr<class IAssetTypeActions>> RegisteredAssetTypeActions;
};

