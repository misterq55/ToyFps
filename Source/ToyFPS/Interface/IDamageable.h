#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

class IDamageable
{
public:
	virtual void SetDamage(float InDamage) = 0;
	virtual void SetHealth(float InHealth) = 0;
	virtual float GetHealth() = 0;
	virtual bool IsDead() = 0;
	virtual void SetDead(bool InDead) = 0;
};