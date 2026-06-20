// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageableStaticMeshActor.h"

float ADamageableStaticMeshActor::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	const float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	SetDamage(FinalDamage);

	return FinalDamage;
}

void ADamageableStaticMeshActor::SetDamage(float InDamage)
{
	Health -= InDamage;
	
	if (Health < 0)
	{
		Health = 0;
		SetDead(true);
	}
}

void ADamageableStaticMeshActor::SetHealth(float InHealth)
{
	Health = InHealth;
}

float ADamageableStaticMeshActor::GetHealth()
{
	return Health;
}

bool ADamageableStaticMeshActor::IsDead()
{
	return bDead;
}

void ADamageableStaticMeshActor::SetDead(bool InDead)
{
	bDead = InDead;
}
