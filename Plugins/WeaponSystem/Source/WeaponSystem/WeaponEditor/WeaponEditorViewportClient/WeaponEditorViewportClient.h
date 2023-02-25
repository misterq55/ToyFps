#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"

class FWeaponEditorViewportClient : public FEditorViewportClient
{
public:
	FWeaponEditorViewportClient(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene);
	virtual ~FWeaponEditorViewportClient() {}

	virtual void Tick(float DeltaSeconds) override;
};