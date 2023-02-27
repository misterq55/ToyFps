#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"

class FWeaponEditor;

class FWeaponEditorViewportClient : public FEditorViewportClient
{
public:
	FWeaponEditorViewportClient(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene, TWeakPtr<FWeaponEditor> InWeaponEditor);
	virtual ~FWeaponEditorViewportClient() {}

	virtual void Tick(float DeltaSeconds) override;

protected:
	TWeakPtr<FWeaponEditor> WeaponEditor;
};