// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Animation/AnimSequence.h"
#include "Animation/BlendSpace.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Camera/CameraComponent.h"
#include "Engine/DamageEvents.h"
#include "ToyFPS/Character/ToyFpsCharacter.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimaryWeapon = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("PrimaryWeapon"));
	Muzzle = CreateOptionalDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Eject = CreateOptionalDefaultSubobject<USceneComponent>(TEXT("Eject"));

	Muzzle->SetupAttachment(PrimaryWeapon);
	Eject->SetupAttachment(Muzzle);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	ResetWeapon();
}

void AWeapon::LineTrace(FVector& OutMuzzleLocation, FVector& OutImactPoint, FRotator& ProjectileRotation)
{
	AToyFpsCharacter* ToyFpsCharacter = Cast<AToyFpsCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!ToyFpsCharacter)
		return;

	FVector StartLocation = ToyFpsCharacter->GetMainCamera()->GetComponentLocation();
	FVector ForwardVector = ToyFpsCharacter->GetMainCamera()->GetForwardVector() * 20000.f;

	float Max = ToyFpsCharacter->GetSpreadCurrent() * 10000.f + WeaponData.BulletSpread;
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

//void AWeapon::ReloadAmmo()
//{
//	WeaponData.AmmoCount = WeaponData.MaxAmmo;
//}

void AWeapon::Tick(float DeltaTime)
{
}
