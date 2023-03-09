// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
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

void AWeaponBase::SetWeaponData(FWeaponData InWeaponData)
{
	WeaponData = InWeaponData;
}

void AWeaponBase::ResetWeapon(const FWeaponData& InWeaponData)
{
	PrimaryWeapon->SetSkeletalMesh(InWeaponData.WeaponMesh);
	Muzzle->SetRelativeTransform(InWeaponData.MuzzleTransform);
	Eject->SetRelativeTransform(InWeaponData.EjectTransform);
}

void AWeaponBase::LineTrace(FVector& OutMuzzleLocation, FVector& OutImactPoint, FRotator& ProjectileRotation)
{
	AFpsCharacterBase* FpsCharacter = Cast<AFpsCharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!FpsCharacter)
		return;

	FVector StartLocation = FpsCharacter->GetMainCamera()->GetComponentLocation();
	FVector ForwardVector = FpsCharacter->GetMainCamera()->GetForwardVector() * 20000.f;

	float Max = FpsCharacter->GetSpreadCurrent() * 10000.f + WeaponData.BulletSpread;
	float Min = Max * -1.f;

	FVector EndLocation = FVector(UKismetMathLibrary::RandomFloatInRange(Min, Max), UKismetMathLibrary::RandomFloatInRange(Min, Max), UKismetMathLibrary::RandomFloatInRange(Min, Max)) + ForwardVector;

	FHitResult HitResult;

	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, FCollisionQueryParams());
	GetWorld()->LineTraceSingleByChannel(HitResult, Muzzle->GetComponentLocation(), HitResult.ImpactPoint, ECollisionChannel::ECC_Visibility, FCollisionQueryParams());

	OutMuzzleLocation = Muzzle->GetComponentLocation();
	OutImactPoint = HitResult.ImpactPoint;

	ProjectileRotation = UKismetMathLibrary::FindLookAtRotation(HitResult.TraceStart, HitResult.TraceEnd);

	if (HitResult.GetActor())
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		FDamageEvent DmgEvent;
		HitResult.GetActor()->TakeDamage(WeaponData.AttackDamage, DmgEvent, PlayerController, HitResult.GetActor());
	}
}

void AWeaponBase::ReloadAmmo()
{
	WeaponData.AmmoCount = WeaponData.MaxAmmo;
}