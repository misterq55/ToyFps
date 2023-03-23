#pragma once

#include "Widgets/SCompoundWidget.h"

class FWeaponEditor;
class UWeaponCrossHairWidget;
class SCanvas;

class SWeaponCrossHair : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeaponCrossHair) {}
	SLATE_END_ARGS()

	// void Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor);
		void Construct(const FArguments& InArgs);
	void SetCrossHairWidget(UWeaponCrossHairWidget* InCrossHairWidget);

private:
	// TWeakPtr<FWeaponEditor> WeaponEditor;
	UWeaponCrossHairWidget* CrossHairWidget = nullptr;
	TSharedPtr<SCanvas> CanvasWidget;
};