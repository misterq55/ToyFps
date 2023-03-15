// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponCrossHairWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "WeaponSystem/Character/FpsCharacterBase.h"

void UWeaponCrossHairWidget::NativeConstruct()
{
	FTimerHandle SetCrossHairHandle;
	GetWorld()->GetTimerManager().SetTimer(SetCrossHairHandle, FTimerDelegate::CreateLambda([&]()
		{
			SetCrossHair();
		}), 0.1f, true);

	FTimerHandle HideWhileADSHandle;
	GetWorld()->GetTimerManager().SetTimer(HideWhileADSHandle, FTimerDelegate::CreateLambda([&]()
		{
			HideWhileADS();
		}), 0.01f, true);

	UCanvasPanel* CanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("CanvasPanel")));
	
	for (UPanelSlot* PanelSlot : CanvasPanel->GetSlots())
	{
		/*UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(PanelSlot);
		FVector2D PositionVector = CanvasPanelSlot->GetPosition();
		PositionVector.Normalize();
		CrossHairUnitVectors.Add(PositionVector);*/

		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(PanelSlot);

		float FlagValue = 1.0;

		FVector2D Position = CanvasPanelSlot->GetPosition();
		if (Position.X * Position.Y < 0)
			FlagValue *= -1.f;

		FlagValues.Add(FlagValue);
	}
	
	OwningCharacter = Cast<AFpsCharacterBase>(GetOwningPlayerPawn());
	
	// Super::NativeConstruct();
}

void UWeaponCrossHairWidget::SetCrossHair()
{
	UCanvasPanel* CanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("CanvasPanel")));
	
	if (!CanvasPanel)
		return;

	float DeltaTimeSeconds = GetWorld()->DeltaTimeSeconds;

	for (int32 i = 0; i < CanvasPanel->GetSlots().Num(); i++)
	{
		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(CanvasPanel->GetSlots()[i]);
		
		if (!CanvasPanelSlot)
			continue;

		FVector Velocity = OwningCharacter->GetVelocity();
		float VelocityLength = Velocity.Length();
		float Target = VelocityLength * 0.4f * -1.f;

		float MapRangedUnclampedValue = UKismetMathLibrary::MapRangeUnclamped(OwningCharacter->GetSpreadCurrent(), 0.f, OwningCharacter->GetSpreadMax(), 0.f, OwningCharacter->GetSpreadMax() * -350.f);
		FVector2D Position = CanvasPanelSlot->GetPosition();

		FVector2D NewPosition =
			FVector2D(UKismetMathLibrary::FInterpTo(Position.X, Target, DeltaTimeSeconds, InterpSpeed),
				UKismetMathLibrary::FInterpTo(Position.Y, Target, DeltaTimeSeconds, InterpSpeed));

		NewPosition.X = UKismetMathLibrary::FClamp(NewPosition.X, UpperBound, LowerBound) + MapRangedUnclampedValue;
		NewPosition.Y = UKismetMathLibrary::FClamp(NewPosition.Y, UpperBound, LowerBound) + MapRangedUnclampedValue;

		NewPosition.X *= FlagValues[i];
		NewPosition.Y *= FlagValues[i];

		CanvasPanelSlot->SetPosition(NewPosition);
	}
}

void UWeaponCrossHairWidget::HideWhileADS()
{
}