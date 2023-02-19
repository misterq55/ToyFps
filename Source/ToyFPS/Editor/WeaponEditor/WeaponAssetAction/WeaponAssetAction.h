#pragma once

#include "AssetTypeActions_Base.h"

class FWeaponAssetAction : public FAssetTypeActions_Base
{
public:
  virtual FText GetName() const override;
  virtual UClass* GetSupportedClass() const override;
  virtual uint32 GetCategories() override;
  virtual FColor GetTypeColor() const override;
  void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor) override;
};