// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponCrossHairWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WeaponSystem/Character/FpsCharacterBase.h"

void UWeaponCrossHairWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CrossHairUnitVectors.Empty();

	UCanvasPanel* const CanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("canvasPanel")));
	if (!IsValid(CanvasPanel))
	{
		return;
	}

	TArray<FVector2D> SlotPositions;
	SlotPositions.Reserve(CanvasPanel->GetSlots().Num());

	for (int32 Index = 0; Index < CanvasPanel->GetSlots().Num(); Index++)
	{
		UCanvasPanelSlot* const CanvasPanelSlot = Cast<UCanvasPanelSlot>(CanvasPanel->GetSlots()[Index]);
		if (!IsValid(CanvasPanelSlot))
		{
			continue;
		}

		SlotPositions.Add(CanvasPanelSlot->GetPosition());
	}

	if (SlotPositions.Num() == 0)
	{
		OwningCharacter = Cast<AFpsCharacterBase>(GetOwningPlayerPawn());
		return;
	}

	FVector2D Centroid = FVector2D::ZeroVector;
	for (const FVector2D& SlotPosition : SlotPositions)
	{
		Centroid += SlotPosition;
	}
	Centroid /= SlotPositions.Num();
	CenterPivot = Centroid;

	for (const FVector2D& SlotPosition : SlotPositions)
	{
		FVector2D UnitVector = SlotPosition - CenterPivot;
		if (UnitVector.IsNearlyZero())
		{
			UnitVector = FVector2D(0.f, -1.f);
		}

		UnitVector.Normalize();
		CrossHairUnitVectors.Add(UnitVector);
	}
	
	OwningCharacter = Cast<AFpsCharacterBase>(GetOwningPlayerPawn());
}

void UWeaponCrossHairWidget::NativeDestruct()
{
	if (UWorld* const World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(SetCrossHairTimerHandle);
	}

	Super::NativeDestruct();
}

void UWeaponCrossHairWidget::SetCrossHair()
{
	UCanvasPanel* const CanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("canvasPanel")));
	
	if (!IsValid(CanvasPanel))
	{
		return;
	}

	UWorld* const World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	const float DeltaTimeSeconds = World->DeltaTimeSeconds;
	
	if (!IsValid(OwningCharacter))
	{
		return;
	}

	UCharacterMovementComponent* const CharacterMovement = OwningCharacter->GetCharacterMovement();
	if (!IsValid(CharacterMovement))
	{
		return;
	}

	const float LowerRadius = FMath::Abs(LowerBound);
	const float UpperRadius = FMath::Abs(UpperBound);
	const float RadiusRange = FMath::Max(UpperRadius - LowerRadius, 0.f);

	const float MaxWalkSpeed = CharacterMovement->MaxWalkSpeed;
	const float MovementAlpha = MaxWalkSpeed > 0.f
		? FMath::Clamp(OwningCharacter->GetVelocity().Size2D() / MaxWalkSpeed, 0.f, 1.f)
		: 0.f;

	const float SpreadRange = OwningCharacter->GetSpreadMax() - OwningCharacter->GetSpreadMin();
	const float SpreadAlpha = SpreadRange > 0.f
		? FMath::Clamp((OwningCharacter->GetSpreadCurrent() - OwningCharacter->GetSpreadMin()) / SpreadRange, 0.f, 1.f)
		: 0.f;

	const float TargetAlpha = FMath::Clamp(MovementAlpha + SpreadAlpha, 0.f, 1.f);
	const float TargetRadius = LowerRadius + (RadiusRange * TargetAlpha);
	const int32 SlotCount = FMath::Min(CanvasPanel->GetSlots().Num(), CrossHairUnitVectors.Num());

	for (int32 Index = 0; Index < SlotCount; Index++)
	{
		UCanvasPanelSlot* const CanvasPanelSlot = Cast<UCanvasPanelSlot>(CanvasPanel->GetSlots()[Index]);

		if (!IsValid(CanvasPanelSlot))
		{
			continue;
		}

		const FVector2D Position = CanvasPanelSlot->GetPosition();
		const FVector2D UnitVector = CrossHairUnitVectors[Index];
		const FVector2D TargetPosition = UnitVector * TargetRadius;
		const FVector2D UpperBoundVector = UnitVector * UpperRadius;
		const FVector2D LowerBoundVector = UnitVector * LowerRadius;
		const FVector2D NewPosition = MakePositionLimit(
			FVector2D(
				UKismetMathLibrary::FInterpTo(Position.X, TargetPosition.X, DeltaTimeSeconds, InterpSpeed),
				UKismetMathLibrary::FInterpTo(Position.Y, TargetPosition.Y, DeltaTimeSeconds, InterpSpeed)),
			UpperBoundVector,
			LowerBoundVector);

		CanvasPanelSlot->SetPosition(NewPosition);
	}
}

void UWeaponCrossHairWidget::HideWhileADS()
{
}

void UWeaponCrossHairWidget::StartTimer()
{
	UWorld* const World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	World->GetTimerManager().ClearTimer(SetCrossHairTimerHandle);
	World->GetTimerManager().SetTimer(SetCrossHairTimerHandle, this, &UWeaponCrossHairWidget::SetCrossHair, 0.1f, true);
}

FVector2D UWeaponCrossHairWidget::MakePositionLimit(const FVector2D& InPosition, const FVector2D& InUpperBoundVector, const FVector2D& InLowerBoundVector)
{
	FVector2D NewPosition = InPosition;

	const float AbsUpperX = FMath::Abs(InUpperBoundVector.X);
	const float AbsLowerX = FMath::Abs(InLowerBoundVector.X);
	const float AbsUpperY = FMath::Abs(InUpperBoundVector.Y);
	const float AbsLowerY = FMath::Abs(InLowerBoundVector.Y);

	const float ClampedAbsX = FMath::Clamp(FMath::Abs(NewPosition.X), AbsLowerX, AbsUpperX);
	const float ClampedAbsY = FMath::Clamp(FMath::Abs(NewPosition.Y), AbsLowerY, AbsUpperY);

	const float SignX = !FMath::IsNearlyZero(InUpperBoundVector.X)
		? FMath::Sign(InUpperBoundVector.X)
		: (!FMath::IsNearlyZero(InLowerBoundVector.X) ? FMath::Sign(InLowerBoundVector.X) : 1.f);
	const float SignY = !FMath::IsNearlyZero(InUpperBoundVector.Y)
		? FMath::Sign(InUpperBoundVector.Y)
		: (!FMath::IsNearlyZero(InLowerBoundVector.Y) ? FMath::Sign(InLowerBoundVector.Y) : 1.f);

	NewPosition.X = ClampedAbsX * SignX;
	NewPosition.Y = ClampedAbsY * SignY;

	return NewPosition;
}
