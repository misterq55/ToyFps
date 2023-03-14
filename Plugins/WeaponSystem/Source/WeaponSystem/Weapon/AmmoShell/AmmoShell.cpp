// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoShell.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AAmmoShell::AAmmoShell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AmmoShellMeshComponent = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoShell"));
	ProjectileMovement = CreateOptionalDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovment"));
}

// Called when the game starts or when spawned
void AAmmoShell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmoShell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}