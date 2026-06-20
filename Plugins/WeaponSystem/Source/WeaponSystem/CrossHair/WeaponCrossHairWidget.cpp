// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponCrossHairWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "WeaponSystem/Character/FpsCharacterBase.h"

void UWeaponCrossHairWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UCanvasPanel* const CanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("canvasPanel")));
	if (!IsValid(CanvasPanel))
	{
		return;
	}

	for (int32 Index = 0; Index < CanvasPanel->GetSlots().Num(); Index++)
	{
		UCanvasPanelSlot* const CanvasPanelSlot = Cast<UCanvasPanelSlot>(CanvasPanel->GetSlots()[Index]);
		const FVector2D PositionVector = CanvasPanelSlot->GetPosition();

		FVector2D UnitVector = CenterPivot - PositionVector;
		UnitVector.Normalize();
		CrossHairUnitVectors.Add(UnitVector);
	}
	
	OwningCharacter = Cast<AFpsCharacterBase>(GetOwningPlayerPawn());
}

void UWeaponCrossHairWidget::SetCrossHair()
{
	UCanvasPanel* const CanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("canvasPanel")));
	
	if (!IsValid(CanvasPanel))
	{
		return;
	}

	const float DeltaTimeSeconds = GetWorld()->DeltaTimeSeconds;
	
	if (!IsValid(OwningCharacter))
	{
		return;
	}

	const float WeaponFirePower = UKismetMathLibrary::MapRangeUnclamped(OwningCharacter->GetSpreadCurrent(), 0.f, OwningCharacter->GetSpreadMax(), 0.f, OwningCharacter->GetSpreadMax() * -350.f);

	for (int32 Index = 0; Index < CanvasPanel->GetSlots().Num(); Index++)
	{
		UCanvasPanelSlot* const CanvasPanelSlot = Cast<UCanvasPanelSlot>(CanvasPanel->GetSlots()[Index]);
		const FVector2D Position = CanvasPanelSlot->GetPosition();

		if (!IsValid(CanvasPanelSlot))
		{
			continue;
		}

		const FVector Velocity = OwningCharacter->GetVelocity();
		const float VelocityLength = Velocity.Length();
		const float Power = VelocityLength * 0.4f * -1.f;
		
		const FVector2D UnitVector = CrossHairUnitVectors[Index];
		const FVector2D PowerVector = UnitVector * Power;
		
		const FVector2D InterpedVector = 
			FVector2D(
				UKismetMathLibrary::FInterpTo(Position.X, PowerVector.X, DeltaTimeSeconds, InterpSpeed),
				UKismetMathLibrary::FInterpTo(Position.Y, PowerVector.Y, DeltaTimeSeconds, InterpSpeed));

		const FVector2D WeaponFirePowerVector = UnitVector * WeaponFirePower * 2.5f;
		const FVector2D NewPosition = MakePositionLimit(InterpedVector + WeaponFirePowerVector, UnitVector * UpperBound, UnitVector * LowerBound);

		CanvasPanelSlot->SetPosition(NewPosition);
	}
}

void UWeaponCrossHairWidget::HideWhileADS()
{
}

void UWeaponCrossHairWidget::StartTimer()
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
}

FVector2D UWeaponCrossHairWidget::MakePositionLimit(const FVector2D& InPosition, const FVector2D& InUpperBoundVector, const FVector2D& InLowerBoundVector)
{
	FVector2D NewPosition = InPosition;

	FVector2D CalcUpperBoundVector = InUpperBoundVector;
	if (CalcUpperBoundVector.X < 0)
		CalcUpperBoundVector.X *= -1.f;
	if (CalcUpperBoundVector.Y < 0)
		CalcUpperBoundVector.Y *= -1.f;

	FVector2D CalcLowerBoundVector = InLowerBoundVector;
	if (CalcLowerBoundVector.X < 0)
		CalcLowerBoundVector.X *= -1.f;
	if (CalcLowerBoundVector.Y < 0)
		CalcLowerBoundVector.Y *= -1.f;

	float CalcX = NewPosition.X;
	if (CalcX < 0)
		CalcX *= -1.f;
	float CalcY = NewPosition.Y;
	if (CalcY < 0)
		CalcY *= -1.f;

	if (CalcX < CalcLowerBoundVector.X)
		NewPosition.X = InLowerBoundVector.X;
	else if (CalcX > CalcUpperBoundVector.X)
		NewPosition.X = InUpperBoundVector.X;

	if (CalcY < CalcLowerBoundVector.Y)
		NewPosition.Y = InLowerBoundVector.Y;
	else if (CalcY > CalcUpperBoundVector.Y)
		NewPosition.Y = InUpperBoundVector.Y;

	return NewPosition;
}
