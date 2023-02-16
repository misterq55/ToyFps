#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

class IDamageable
{
public:
	virtual void SetDamage(float InDamage) = 0;
	virtual void SetHP(float InHP) = 0;
	virtual float GetHP() = 0;
	virtual bool GetDead() = 0;
	virtual void SetDead(bool InDead) = 0;
};