// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponCrossHairWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "WeaponSystem/Character/FpsCharacterBase.h"

void UWeaponCrossHairWidget::NativeConstruct()
{
	Super::NativeConstruct();

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
		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(PanelSlot);
		FVector2D PositionVector = CanvasPanelSlot->GetPosition();
		InitialPositionVectors.Add(PositionVector);

		FVector2D UnitVector = CenterPivot - PositionVector;
		UnitVector.Normalize();
		CrossHairUnitVectors.Add(UnitVector);
	}
	
	OwningCharacter = Cast<AFpsCharacterBase>(GetOwningPlayerPawn());
}

void UWeaponCrossHairWidget::SetCrossHair()
{
	UCanvasPanel* CanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("CanvasPanel")));
	
	if (!CanvasPanel)
		return;

	float DeltaTimeSeconds = GetWorld()->DeltaTimeSeconds;
	
	// 무기 발사에 의한 크로스 헤어 벌어짐
	float MapRangedUnclampedValue = UKismetMathLibrary::MapRangeUnclamped(OwningCharacter->GetSpreadCurrent(), 0.f, OwningCharacter->GetSpreadMax(), 0.f, OwningCharacter->GetSpreadMax() * -350.f);

	// FInterpTo
	// FClamp

	for (int32 i = 0; i < CanvasPanel->GetSlots().Num(); i++)
	{
		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(CanvasPanel->GetSlots()[i]);
		FVector2D Position = CanvasPanelSlot->GetPosition();

		if (!CanvasPanelSlot)
			continue;

		FVector Velocity = OwningCharacter->GetVelocity();
		float VelocityLength = Velocity.Length();
		float Target = VelocityLength * 0.4f * -1.f;

		FVector2D PowerVector = CrossHairUnitVectors[i] * (Target + MapRangedUnclampedValue * 100);
		
		FVector2D InterpedVector;
		InterpedVector.X = UKismetMathLibrary::FInterpTo(Position.X, PowerVector.X, DeltaTimeSeconds, InterpSpeed);
		InterpedVector.Y = UKismetMathLibrary::FInterpTo(Position.Y, PowerVector.Y, DeltaTimeSeconds, InterpSpeed);

		float FlagValue = 1.f;
		if (Position.X * Position.Y < 0)
			FlagValue *= -1.f;

		FVector2D UpperBoundVector = CrossHairUnitVectors[i] * UpperBound * FlagValue;
		FVector2D LowerBoundVector = CrossHairUnitVectors[i] * LowerBound * FlagValue;

		FVector2D NewPosition;
		NewPosition.X = UKismetMathLibrary::FClamp(InterpedVector.X, UpperBoundVector.X, LowerBoundVector.X);
		NewPosition.Y = UKismetMathLibrary::FClamp(InterpedVector.Y, UpperBoundVector.Y, LowerBoundVector.Y);

		CanvasPanelSlot->SetPosition(NewPosition);
	}
}

void UWeaponCrossHairWidget::HideWhileADS()
{
}