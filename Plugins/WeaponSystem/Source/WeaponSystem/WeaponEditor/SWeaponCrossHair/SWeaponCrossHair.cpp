#include "SWeaponCrossHair.h"
#include "WeaponSystem/WeaponEditor/WeaponEditor.h"
#include "WeaponSystem/CrossHair/WeaponCrossHairWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Widgets/SCanvas.h"

// void SWeaponCrossHair::Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor)
void SWeaponCrossHair::Construct(const FArguments& InArgs)
{
	// WeaponEditor = InSpriteEditor;
	SAssignNew(CanvasWidget, SCanvas);
	// SCompoundWidget::Construct();
}

void SWeaponCrossHair::SetCrossHairWidget(UWeaponCrossHairWidget* InCrossHairWidget)
{
	CrossHairWidget = InCrossHairWidget;

	if (!CrossHairWidget)
		return;

	CrossHairWidget->SetCenterPivot(FVector2D(-4.960938, -12.540527));
	CrossHairWidget->NativeConstruct();
	
	UCanvasPanel* CanvasPanel = Cast<UCanvasPanel>(CrossHairWidget->GetWidgetFromName(TEXT("CanvasPanel")));

	for (int32 i = 0; i < CanvasPanel->GetSlots().Num(); i++)
	{
		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(CanvasPanel->GetSlots()[i]);
		UImage* Image = Cast<UImage>(CanvasPanel->GetChildAt(i));
		
		FVector2D Position = CanvasPanelSlot->GetPosition();
		FVector2D Size = CanvasPanelSlot->GetSize();

		CanvasWidget->AddSlot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.Size(CanvasPanelSlot->GetSize() * 10)
			.Position(CanvasPanelSlot->GetPosition())
			[
				SNew(SImage)
				.Image(&Image->Brush)
			]
			;
	}

	ChildSlot
		[
			CanvasWidget.ToSharedRef()
		];
}
