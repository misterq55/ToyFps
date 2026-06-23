// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponCrossHairWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WeaponSystem/Character/FpsCharacterBase.h"
#include "WeaponSystem/Weapon/WeaponBase.h"
#include "Camera/CameraComponent.h"

void UWeaponCrossHairWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OwningCharacter = Cast<AFpsCharacterBase>(GetOwningPlayerPawn());
	
	CrossHairUnitVectors.Empty();

	UCanvasPanel* const CanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("canvasPanel")));
	if (!IsValid(CanvasPanel))
	{
		return;
	}

	TArray<FVector2D> SlotPositions;
	const int32 SlotNum = CanvasPanel->GetSlots().Num();
	SlotPositions.Reserve(SlotNum);

	for (int32 Index = 0; Index < SlotNum; Index++)
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
}

void UWeaponCrossHairWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (!IsValid(OwningCharacter))
	{
		OwningCharacter = Cast<AFpsCharacterBase>(GetOwningPlayerPawn());
	}
	
	if (IsValid(OwningCharacter))
	{
		const float ScreenHalfWidth = MyGeometry.GetLocalSize().X * 0.5f;
		const float HalfFovTan = FMath::Tan(FMath::DegreesToRadians(OwningCharacter->GetMainCamera()->FieldOfView * 0.5f));
		CachedPixelFactor = (HalfFovTan > 0.f) ? ScreenHalfWidth / HalfFovTan : 0.f;
	}
	
	HideWhileADS();
	
	SetCrossHair();
}

void UWeaponCrossHairWidget::SetCrossHair()
{
	const float DeltaTimeSeconds = GetWorld()->DeltaTimeSeconds;

	if (!IsValid(OwningCharacter))
	{
		return;
	}

	AWeaponBase* const CurrentWeapon = OwningCharacter->GetCurrentWeapon();
	const FWeaponData& WeaponData = IsValid(CurrentWeapon) ? CurrentWeapon->GetWeaponData() : FWeaponData();

	// 발사 반동에 따른 크로스헤어 확산 목표값 계산
	const float HalfAngleRad = FMath::DegreesToRadians(OwningCharacter->GetSpreadCurrent() + WeaponData.BulletSpread);
	const float TargetFirePower = FMath::Tan(HalfAngleRad) * CachedPixelFactor;

	// 발사 시 빠르게 벌어지고, 회복 시 천천히 복귀
	const float FirePowerInterpSpeed = (TargetFirePower > CurrentFirePower) ? FirePowerInterpSpeedSpread : FirePowerInterpSpeedRecover;
	CurrentFirePower = UKismetMathLibrary::FInterpTo(CurrentFirePower, TargetFirePower, DeltaTimeSeconds, FirePowerInterpSpeed);

	UCharacterMovementComponent* const CharacterMovement = OwningCharacter->GetCharacterMovement();
	if (!IsValid(CharacterMovement))
	{
		return;
	}
	
	const FVector Velocity = OwningCharacter->GetVelocity();
	const float VelocityLength = FVector(Velocity.X, Velocity.Y, 0.f).Length();
	const float Power = CharacterMovement->IsFalling()
		? AirSpreadPower
		: VelocityLength * 0.4f;

	UCanvasPanel* const CanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("canvasPanel")));
	if (!IsValid(CanvasPanel))
	{
		return;
	}

	const int32 SlotNum = CanvasPanel->GetSlots().Num();
	for (int32 i = 0; i < SlotNum; i++)
	{
		UCanvasPanelSlot* const CanvasPanelSlot = Cast<UCanvasPanelSlot>(CanvasPanel->GetSlots()[i]);

		if (!IsValid(CanvasPanelSlot))
		{
			continue;
		}

		const FVector2D UnitVector = CrossHairUnitVectors[i];

		// target = velocity spread + fire spread
		const float TargetSpread = Power + CurrentFirePower;

		// interp from current position toward target (no feedback loop)
		const FVector2D CurrentPos = CanvasPanelSlot->GetPosition();
		const float CurrentProjection = FVector2D::DotProduct(CurrentPos, UnitVector);
		const float InterpedProjection = UKismetMathLibrary::FInterpTo(CurrentProjection, TargetSpread, DeltaTimeSeconds, InterpSpeed);
		const float TotalDisplacementScalar = InterpedProjection;

		// UnitVector 축에 투영해 바운드 클램프
		const float LowerBound = FMath::Tan(FMath::DegreesToRadians(WeaponData.SpreadMin)) * CachedPixelFactor;
		const float UpperBound = FMath::Tan(FMath::DegreesToRadians(WeaponData.SpreadMax + WeaponData.BulletSpread)) * CachedPixelFactor;
		const float ClampedProjection = FMath::Clamp(TotalDisplacementScalar, LowerBound, UpperBound);

		CanvasPanelSlot->SetPosition(UnitVector * ClampedProjection);
	}
}

void UWeaponCrossHairWidget::HideWhileADS()
{
	UCanvasPanel* const CanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("canvasPanel")));
	if (!IsValid(OwningCharacter) || !IsValid(CanvasPanel))
	{
		return;
	}

	const ESlateVisibility newVisibility = OwningCharacter->IsAimingDownSight()
		? ESlateVisibility::Hidden
		: ESlateVisibility::Visible;

	CanvasPanel->SetVisibility(newVisibility);
}
