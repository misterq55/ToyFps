// Copyright Epic Games, Inc. All Rights Reserved.

#include "WeaponSystem.h"

#define LOCTEXT_NAMESPACE "FWeaponSystemModule"

void FWeaponSystemModule::StartupModule()
{
	// Runtime module startup remains empty; editor registration moved to WeaponEditor module.
}

void FWeaponSystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWeaponSystemModule, WeaponSystem)