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

	void Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor);
	void SetCrossHairWidget(UWeaponCrossHairWidget* InCrossHairWidget);
	void SetCenterPivot(FVector2D InCenterPivot);

private:
	TWeakPtr<FWeaponEditor> WeaponEditor;
	UWeaponCrossHairWidget* CrossHairWidget = nullptr;
	TSharedPtr<SCanvas> CanvasWidget;
	FVector2D CenterPivot;
};