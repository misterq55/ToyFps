#pragma once

#include "Widgets/SCompoundWidget.h"

class FWeaponEditor;

class SWeaponAnimationAssets : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeaponAnimationAssets) {}
	SLATE_END_ARGS()

		void Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor);

private:
	TWeakPtr<FWeaponEditor> WeaponEditor;
	TSharedPtr<FAssetThumbnailPool> AssetThumbnailPool;
};