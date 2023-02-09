// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

AGun::AGun()
{
	Muzzle = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("Muzzle"));
	Eject = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("Eject"));

	Muzzle->SetupAttachment(PrimaryWeapon);
	Eject->SetupAttachment(Muzzle);
}