// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "ToyFPS/Interface/IDamageable.h"
#include "DamageableStaticMeshActor.generated.h"

/**
 * 
 */
UCLASS()
class TOYFPS_API ADamageableStaticMeshActor : public AStaticMeshActor, public IDamageable
{
	GENERATED_BODY()
	
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void SetDamage(float InDamage);
	virtual void SetHP(float InHP);
	virtual float GetHP();
	virtual bool GetDead();
	virtual void SetDead(bool InDead);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Damageable, meta = (AllowPrivateAccess = "true"))
		float HP = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Damageable, meta = (AllowPrivateAccess = "true"))
		bool bDead = false;
};
