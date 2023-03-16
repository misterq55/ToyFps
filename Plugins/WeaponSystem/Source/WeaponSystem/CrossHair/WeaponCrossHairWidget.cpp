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
	if (!CanvasPanel)
		return;

	for (int32 i = 0; i < CanvasPanel->GetSlots().Num(); i++)
	{
		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(CanvasPanel->GetSlots()[i]);
		FVector2D PositionVector = CanvasPanelSlot->GetPosition();

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
	float WeaponFirePower = UKismetMathLibrary::MapRangeUnclamped(OwningCharacter->GetSpreadCurrent(), 0.f, OwningCharacter->GetSpreadMax(), 0.f, OwningCharacter->GetSpreadMax() * -350.f);

	for (int32 i = 0; i < CanvasPanel->GetSlots().Num(); i++)
	{
		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(CanvasPanel->GetSlots()[i]);
		FVector2D Position = CanvasPanelSlot->GetPosition();

		if (!CanvasPanelSlot)
			continue;

		FVector Velocity = OwningCharacter->GetVelocity();
		float VelocityLength = Velocity.Length();
		float Power = VelocityLength * 0.4f * -1.f;
		
		FVector2D UnitVector = CrossHairUnitVectors[i];
		FVector2D PowerVector = UnitVector * Power;
		
		FVector2D InterpedVector = 
			FVector2D(
				UKismetMathLibrary::FInterpTo(Position.X, PowerVector.X, DeltaTimeSeconds, InterpSpeed),
			UKismetMathLibrary::FInterpTo(Position.Y, PowerVector.Y, DeltaTimeSeconds, InterpSpeed));

		if (UnitVector.X * UnitVector.Y > 0)
			Swap(UpperBound, LowerBound);

		FVector2D UpperBoundVector = UnitVector * UpperBound;
		FVector2D LowerBoundVector = UnitVector * LowerBound;

		FVector2D WeaponFirePowerVector = UnitVector * WeaponFirePower * 2.5f;

		FVector2D NewPosition;
		NewPosition.X = UKismetMathLibrary::FClamp(InterpedVector.X, UpperBoundVector.X, LowerBoundVector.X) + WeaponFirePowerVector.X;
		NewPosition.Y = UKismetMathLibrary::FClamp(InterpedVector.Y, UpperBoundVector.Y, LowerBoundVector.Y) + WeaponFirePowerVector.Y;

		CanvasPanelSlot->SetPosition(NewPosition);
	}
}

void UWeaponCrossHairWidget::HideWhileADS()
{
}