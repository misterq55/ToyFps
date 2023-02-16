// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageableStaticMeshActor.h"

float ADamageableStaticMeshActor::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = 0.f;

	FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	SetDamage(FinalDamage);

	return FinalDamage;
}

void ADamageableStaticMeshActor::SetDamage(float InDamage)
{
	HP -= InDamage;
	
	if (HP < 0)
	{
		HP = 0;
		SetDead(true);
	}
}

void ADamageableStaticMeshActor::SetHP(float InHP)
{
	HP = InHP;
}

float ADamageableStaticMeshActor::GetHP()
{
	return HP;
}

bool ADamageableStaticMeshActor::GetDead()
{
	return bDead;
}

void ADamageableStaticMeshActor::SetDead(bool InDead)
{
	bDead = InDead;
}
