// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoShell.generated.h"

UCLASS()
class WEAPONSYSTEM_API AAmmoShell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoShell();
	virtual bool ShouldTickIfViewportsOnly() const
	{
		return true;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(Category = AmmoShell, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UStaticMeshComponent> AmmoShellMeshComponent;

	UPROPERTY(Category = AmmoShell, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;

};