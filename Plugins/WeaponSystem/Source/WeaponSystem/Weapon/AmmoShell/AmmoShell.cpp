// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoShell.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AAmmoShell::AAmmoShell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = AmmoShellMeshComponent = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoShell"));
	ProjectileMovement = CreateOptionalDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovment"));
}

// Called when the game starts or when spawned
void AAmmoShell::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle WaitHandle;
	float WaitTime = 10.f; 
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			Destroy();
		}), WaitTime, false); 
}

void AAmmoShell::ApplyPhysics()
{
	if (!AmmoShellMeshComponent)
		return;

	AmmoShellMeshComponent->BodyInstance.bSimulatePhysics = true;
	AmmoShellMeshComponent->BodyInstance.WeldParent = false;
	BeginPlay();
}

// Called every frame
void AAmmoShell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}