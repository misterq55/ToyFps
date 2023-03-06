// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

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

void AWeapon::Tick(float DeltaTime)
{
}
