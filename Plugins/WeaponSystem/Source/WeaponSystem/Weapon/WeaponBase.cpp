// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "Engine/DamageEvents.h"
#include "WeaponSystem/Character/FpsCharacterBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::SetWeaponData(FWeaponData weaponData)
{
	WeaponData = weaponData;
}

void AWeaponBase::ResetWeapon(const FWeaponData& weaponData)
{
	PrimaryWeapon->SetSkeletalMesh(weaponData.WeaponMesh);
	Muzzle->SetRelativeTransform(weaponData.MuzzleTransform);
	Eject->SetRelativeTransform(weaponData.EjectTransform);
}

void AWeaponBase::LineTrace(FVector& muzzleLocation, FVector& imactPoint, FRotator& projectileRotation)
{
	AFpsCharacterBase* FpsCharacter = Cast<AFpsCharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!IsValid(FpsCharacter))
	{
		return;
	}

	FVector startLocation = FpsCharacter->GetMainCamera()->GetComponentLocation();
	FVector forwardVector = FpsCharacter->GetMainCamera()->GetForwardVector() * 20000.f;

	float max = FpsCharacter->GetSpreadCurrent() * 10000.f + WeaponData.BulletSpread;
	float min = max * -1.f;

	FVector endLocation = FVector(UKismetMathLibrary::RandomFloatInRange(min, max), UKismetMathLibrary::RandomFloatInRange(min, max), UKismetMathLibrary::RandomFloatInRange(min, max)) + forwardVector;

	FHitResult hitResult;

	GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECollisionChannel::ECC_Visibility, FCollisionQueryParams());
	GetWorld()->LineTraceSingleByChannel(hitResult, Muzzle->GetComponentLocation(), hitResult.ImpactPoint, ECollisionChannel::ECC_Visibility, FCollisionQueryParams());

	muzzleLocation = Muzzle->GetComponentLocation();
	imactPoint = hitResult.ImpactPoint;

	projectileRotation = UKismetMathLibrary::FindLookAtRotation(hitResult.TraceStart, hitResult.TraceEnd);

	if (hitResult.GetActor())
	{
		APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		FDamageEvent dmgEvent;
		hitResult.GetActor()->TakeDamage(WeaponData.AttackDamage, dmgEvent, playerController, hitResult.GetActor());
	}
}

void AWeaponBase::ReloadAmmo()
{
	WeaponData.AmmoCount = WeaponData.MaxAmmo;
}