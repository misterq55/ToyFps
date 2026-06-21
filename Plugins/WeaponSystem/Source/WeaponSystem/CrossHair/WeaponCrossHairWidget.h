// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponCrossHairWidget.generated.h"

/**
 * 
 */
UCLASS()
class WEAPONSYSTEM_API UWeaponCrossHairWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	void SetCrossHair();
	void HideWhileADS();
	void SetCenterPivot(const FVector2D& InCenterPivot) {
		CenterPivot = InCenterPivot;
	}
	
	void SetOwningCharacter(TObjectPtr<class AFpsCharacterBase> InCharacter) {
		OwningCharacter = InCharacter;
	}

	void StartTimer();

private:
	FVector2D MakePositionLimit(const FVector2D& InPosition, const FVector2D& InUpperBoundVector, const FVector2D& InLowerBoundVector);
	FTimerHandle SetCrossHairTimerHandle;

protected:
	TArray<FVector2D> CrossHairUnitVectors;
	TObjectPtr<class AFpsCharacterBase> OwningCharacter;

	// UPROPERTY(Category = CrossHair, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	// 	float InterpSpeed = 3.f;
	//
	// UPROPERTY(Category = CrossHair, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	// 	float UpperBound = -250.f;
	//
	// UPROPERTY(Category = CrossHair, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	// 	float LowerBound = -25.f;
	//
	// UPROPERTY(Category = CrossHair, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	// 	FVector2D CenterPivot;
	
	float CurrentFirePower = 0.f;
	float CachedPixelFactor = 0.f;

	UPROPERTY(Category = CrossHair, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float InterpSpeed = 3.f;

	UPROPERTY(Category = CrossHair, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float FirePowerInterpSpeedSpread = 20.f;

	UPROPERTY(Category = CrossHair, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float FirePowerInterpSpeedRecover = 5.f;

	UPROPERTY(Category = CrossHair, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AirSpreadPower = 80.f;

	UPROPERTY(Category = CrossHair, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector2D CenterPivot;
};
