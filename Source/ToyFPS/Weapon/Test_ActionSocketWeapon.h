// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Test_ActionSocketWeapon.generated.h"

/**
 * 
 */

class UWeaponAction;

UCLASS()
class TOYFPS_API ATest_ActionSocketWeapon : public AWeapon
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = WeaponAction, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UWeaponAction* AttackAction = nullptr;

	UPROPERTY(Category = WeaponAction, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UWeaponAction* ReloadAction = nullptr;

	UPROPERTY(Category = WeaponAction, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UWeaponAction* AimDownSightAction = nullptr;

	UPROPERTY(Category = WeaponAction, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UWeaponAction* SniperZoomAction = nullptr;

public:
	virtual void Attack() override;
	virtual void StopAttacking() override;
	virtual void Reload() override;
	virtual void SniperZoom(bool Toggle) override;
};
