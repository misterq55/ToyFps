#pragma once

#include "CoreMinimal.h"
#include "WeaponEditorViewportClient.h"

class FWeaponEditorViewportClient_Editor : public FWeaponEditorViewportClient
{
public:
	FWeaponEditorViewportClient_Editor(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene);
	virtual ~FWeaponEditorViewportClient_Editor() {}

	virtual void Tick(float DeltaSeconds) override;
};