#pragma once

#include "Widgets/SCompoundWidget.h"

class FWeaponEditor;
class SWeaponAbilities : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeaponAbilities) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor);

private:
	TWeakPtr<FWeaponEditor> WeaponEditor;
};