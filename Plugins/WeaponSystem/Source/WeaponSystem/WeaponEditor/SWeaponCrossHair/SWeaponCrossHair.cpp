#include "SWeaponCrossHair.h"
#include "WeaponSystem/WeaponEditor/WeaponEditor.h"
#include "WeaponSystem/CrossHair/WeaponCrossHairWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Widgets/SCanvas.h"

#include "WeaponSystem/WeaponEditor/WeaponEditorViewModel/WeaponEditorViewModel.h"

void SWeaponCrossHair::Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor)
{
	WeaponEditor = InSpriteEditor;
	SAssignNew(CanvasWidget, SCanvas);

	TWeakPtr<FViewModelCrossHairObject> ViewModelCrossHairObject = WeaponEditor.Pin()->GetViewModel()->GetViewModelCrossHairObject();

	SetCenterPivot(ViewModelCrossHairObject.Pin()->GetCenterPivot());
	ViewModelCrossHairObject.Pin()->OnSetCenterPivot.Unbind();
	ViewModelCrossHairObject.Pin()->OnSetCenterPivot.BindRaw(this, &SWeaponCrossHair::SetCenterPivot);

	UWeaponCrossHairWidget* CrossHair = ViewModelCrossHairObject.Pin()->GetCrossHair();
	if (CrossHair)
		SetCrossHairWidget(CrossHair);

	ViewModelCrossHairObject.Pin()->OnSetCrossHair.Unbind();
	ViewModelCrossHairObject.Pin()->OnSetCrossHair.BindRaw(this, &SWeaponCrossHair::SetCrossHairWidget);
}

void SWeaponCrossHair::SetCrossHairWidget(UWeaponCrossHairWidget* InCrossHairWidget)
{
	CrossHairWidget = InCrossHairWidget;

	if (!CrossHairWidget)
		return;

	CrossHairWidget->SetCenterPivot(FVector2D(-4.960938, -12.540527));
	CrossHairWidget->NativeConstruct();
	
	CanvasWidget->ClearChildren();

	UCanvasPanel* CanvasPanel = Cast<UCanvasPanel>(CrossHairWidget->GetWidgetFromName(TEXT("CanvasPanel")));

	if (!CanvasPanel)
		return;

	for (int32 i = 0; i < CanvasPanel->GetSlots().Num(); i++)
	{
		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(CanvasPanel->GetSlots()[i]);
		UImage* Image = Cast<UImage>(CanvasPanel->GetChildAt(i));
		FAnchors Anchors = CanvasPanelSlot->GetAnchors();
		FVector2D Position = CanvasPanelSlot->GetPosition() + CenterPivot;
		FVector2D Size = CanvasPanelSlot->GetSize();
		
		FWidgetTransform WidgetTransform = Image->GetRenderTransform();
		FSlateRenderTransform SlateRenderTranform(Concatenate(WidgetTransform.Translation, FQuat2D(FMath::DegreesToRadians(WidgetTransform.Angle))));
		
		CanvasWidget->AddSlot()
			 .HAlign(HAlign_Center)
			 .VAlign(VAlign_Center)
			 .Size(Size)
			 .Position(Position)
			[
				SNew(SImage)
				.Image(&Image->Brush)
				.RenderTransformPivot(Anchors.Minimum)
				.RenderTransform(SlateRenderTranform)
			]
			;
	}

	ChildSlot
		[
			CanvasWidget.ToSharedRef()
		];
}

void SWeaponCrossHair::SetCenterPivot(FVector2D InCenterPivot)
{
	CenterPivot = InCenterPivot;

	SetCrossHairWidget(CrossHairWidget);
}
