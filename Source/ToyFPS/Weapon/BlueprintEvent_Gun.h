// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "BlueprintEvent_Gun.generated.h"

/**
 * 
 */
UCLASS()
class TOYFPS_API ABlueprintEvent_Gun : public AGun
{
	GENERATED_BODY()

public:
	virtual void Attack();
	virtual void Reload();
	virtual void Undraw();
	virtual void Draw();
	virtual void Equipe();
	virtual void StopAttacking();
	virtual void SecondartAttack();
	virtual void SniperZoom(bool Toggle);
	virtual void HideMuzzleFlash();
	virtual void UnHideMuzzleFlash();

	UFUNCTION(BlueprintNativeEvent, Category = Weapon)
		void Attack_BluePrint();

	UFUNCTION(BlueprintNativeEvent, Category = Weapon)
		void Reload_BluePrint();

	UFUNCTION(BlueprintNativeEvent, Category = Weapon)
		void Undraw_BluePrint();

	UFUNCTION(BlueprintNativeEvent, Category = Weapon)
		void Draw_BluePrint();

	UFUNCTION(BlueprintNativeEvent, Category = Weapon)
		void Equipe_BluePrint();

	UFUNCTION(BlueprintNativeEvent, Category = Weapon)
		void StopAttacking_BluePrint();

	UFUNCTION(BlueprintNativeEvent, Category = Weapon)
		void SecondartAttack_BluePrint();

	UFUNCTION(BlueprintNativeEvent, Category = Weapon)
		void SniperZoom_BluePrint(bool Toggle);

	UFUNCTION(BlueprintNativeEvent, Category = Weapon)
		void HideMuzzleFlash_BluePrint();

	UFUNCTION(BlueprintNativeEvent, Category = Weapon)
		void UnhideMuzzleFlash_BluePrint();
};
