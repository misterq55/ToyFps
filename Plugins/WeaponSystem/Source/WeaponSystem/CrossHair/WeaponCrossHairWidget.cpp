// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponCrossHairWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/canvasPanel.h"
#include "Components/canvasPanelSlot.h"
#include "WeaponSystem/Character/FpsCharacterBase.h"

void UWeaponCrossHairWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UCanvasPanel* canvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("canvasPanel")));
	if (!IsValid(canvasPanel))
	{
		return;
	}

	for (int32 i = 0; i < canvasPanel->GetSlots().Num(); i++)
	{
		UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(canvasPanel->GetSlots()[i]);
		FVector2D positionVector = canvasPanelSlot->GetPosition();

		FVector2D unitVector = CenterPivot - positionVector;
		unitVector.Normalize();
		CrossHairUnitVectors.Add(unitVector);
	}
	
	OwningCharacter = Cast<AFpsCharacterBase>(GetOwningPlayerPawn());
}

void UWeaponCrossHairWidget::SetCrossHair()
{
	UCanvasPanel* canvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("canvasPanel")));
	
	if (!IsValid(canvasPanel))
	{
		return;
	}

	float deltaTimeSeconds = GetWorld()->DeltaTimeSeconds;
	
	if (!IsValid(OwningCharacter))
	{
		return;
	}

	// ���� �߻翡 ���� ũ�ν� ��� ������
	float weaponFirePower = UKismetMathLibrary::MapRangeUnclamped(OwningCharacter->GetSpreadCurrent(), 0.f, OwningCharacter->GetSpreadMax(), 0.f, OwningCharacter->GetSpreadMax() * -350.f);

	for (int32 i = 0; i < canvasPanel->GetSlots().Num(); i++)
	{
		UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(canvasPanel->GetSlots()[i]);
		FVector2D position = canvasPanelSlot->GetPosition();

		if (!IsValid(canvasPanelSlot))
		{
			continue;
		}

		FVector velocity = OwningCharacter->GetVelocity();
		float velocityLength = velocity.Length();
		float power = velocityLength * 0.4f * -1.f;
		
		FVector2D unitVector = CrossHairUnitVectors[i];
		FVector2D PowerVector = unitVector * power;
		
		FVector2D interpedVector = 
			FVector2D(
				UKismetMathLibrary::FInterpTo(position.X, PowerVector.X, deltaTimeSeconds, InterpSpeed),
			UKismetMathLibrary::FInterpTo(position.Y, PowerVector.Y, deltaTimeSeconds, InterpSpeed));

		FVector2D weaponFirePowerVector = unitVector * weaponFirePower * 2.5f;
		FVector2D newPosition = MakePositionLimit(interpedVector + weaponFirePowerVector, unitVector * UpperBound, unitVector * LowerBound);

		canvasPanelSlot->SetPosition(newPosition);
	}
}

void UWeaponCrossHairWidget::HideWhileADS()
{
}

void UWeaponCrossHairWidget::StartTimer()
{
	FTimerHandle setCrossHairHandle;
	GetWorld()->GetTimerManager().SetTimer(setCrossHairHandle, FTimerDelegate::CreateLambda([&]()
		{
			SetCrossHair();
		}), 0.1f, true);

	FTimerHandle hideWhileADSHandle;
	GetWorld()->GetTimerManager().SetTimer(hideWhileADSHandle, FTimerDelegate::CreateLambda([&]()
		{
			HideWhileADS();
		}), 0.01f, true);
}

FVector2D UWeaponCrossHairWidget::MakePositionLimit(const FVector2D& position, const FVector2D& upperBoundVector, const FVector2D& lowerBoundVector)
{
	FVector2D newPosition = position;

	FVector2D calcUpperBoundVector = upperBoundVector;
	if (calcUpperBoundVector.X < 0)
		calcUpperBoundVector.X *= -1.f;
	if (calcUpperBoundVector.Y < 0)
		calcUpperBoundVector.Y *= -1.f;

	FVector2D calcLowerBoundVector = lowerBoundVector;
	if (calcLowerBoundVector.X < 0)
		calcLowerBoundVector.X *= -1.f;
	if (calcLowerBoundVector.Y < 0)
		calcLowerBoundVector.Y *= -1.f;

	float calcX = newPosition.X;
	if (calcX < 0)
		calcX *= -1.f;
	float calcY = newPosition.Y;
	if (calcY < 0)
		calcY *= -1.f;

	if (calcX < calcLowerBoundVector.X)
		newPosition.X = lowerBoundVector.X;
	else if (calcX > calcUpperBoundVector.X)
		newPosition.X = upperBoundVector.X;

	if (calcY < calcLowerBoundVector.Y)
		newPosition.Y = lowerBoundVector.Y;
	else if (calcY > calcUpperBoundVector.Y)
		newPosition.Y = upperBoundVector.Y;

	return newPosition;
}
