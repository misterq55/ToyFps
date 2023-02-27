#pragma once

#include "CoreMinimal.h"
#include "WeaponEditorViewportClient.h"

class FWeaponEditorViewportClient_FirstPerson : public FWeaponEditorViewportClient
{
public:
	FWeaponEditorViewportClient_FirstPerson(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene, TWeakPtr<FWeaponEditor> InWeaponEditor);
	virtual ~FWeaponEditorViewportClient_FirstPerson() {}

	virtual void Tick(float DeltaSeconds) override;
};