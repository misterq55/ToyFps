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

	for (int32 i = 0; i < CanvasPanel->GetSlots().Num(); i++)
	{
		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(CanvasPanel->GetSlots()[i]);
		
		if (!CanvasPanelSlot)
			continue;

		FVector Velocity = OwningCharacter->GetVelocity();
		float VelocityLength = Velocity.Length();
		float Target = VelocityLength * 0.4f * -1.f;
		Target *= 0.5f;

		// 무기 발사에 의한 크로스 헤어 벌어짐
		float MapRangedUnclampedValue = UKismetMathLibrary::MapRangeUnclamped(OwningCharacter->GetSpreadCurrent(), 0.f, OwningCharacter->GetSpreadMax(), 0.f, OwningCharacter->GetSpreadMax() * -350.f);
		float Power = Target + MapRangedUnclampedValue;
		CanvasPanelSlot->SetPosition(InitialPositionVectors[i] + CrossHairUnitVectors[i] * Power);
	}
}

void UWeaponCrossHairWidget::HideWhileADS()
{
}