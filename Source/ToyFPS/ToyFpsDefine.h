#pragma once
#include "CoreMinimal.h"
#include "ToyFpsDefine.generated.h"

UENUM(BlueprintType)
enum class EWeaponEquipPose : uint8
{
	None,
	RIFLE1,
	RIFLE2,
	RIFLE3,
	RIFLE4,
	RIFLE5,
	RIFLE6,
	SIDEARM1,
	SIDEARM2,
	SIDEARM3,
	SNIPER1,
	SNIPER2,
	SNIPER3,
	SHOTGUN1,
	SHOTGUN2,
	SHOTGUN3,
	SHOTGUN4,
	SUBMACHINEGUN1,
	SUBMACHINEGUN2,
	SUBMACHINEGUN3,
	SUBMACHINEGUN4,
	SUBMACHINEGUN5,
};

USTRUCT(BlueprintType)
struct TOYFPS_API FWeaponData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		EWeaponEquipPose Pose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		int32 AmmoCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		int32 MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		float ReloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		float BuleetSpread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		float UndrawTime;
};