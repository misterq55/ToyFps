#include "WeaponEditorViewportClient.h"

FWeaponEditorViewportClient::FWeaponEditorViewportClient(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene, TWeakPtr<FWeaponEditor> InWeaponEditor)
	: FEditorViewportClient(InModeTools, InPreviewScene, nullptr)
{
	WeaponEditor = InWeaponEditor;
}

void FWeaponEditorViewportClient::Tick(float DeltaSeconds)
{
	Invalidate();
	FEditorViewportClient::Tick(DeltaSeconds);
}
