// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponSystem/Weapon/WeaponBase.h"
#include "BlueprintEvent_Weapon.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TOYFPS_API ABlueprintEvent_Weapon : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	ABlueprintEvent_Weapon();

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

		UFUNCTION(BlueprintCallable, Category = Weapon)
			float GetBulletSpread() {
			return WeaponData.BulletSpread;
		}

		UFUNCTION(BlueprintCallable, Category = Weapon)
			float GetReloadTime() {
			return WeaponData.ReloadTime;
		}

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
