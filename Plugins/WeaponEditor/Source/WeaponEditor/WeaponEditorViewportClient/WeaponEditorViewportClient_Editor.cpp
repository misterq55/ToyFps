#include "WeaponEditorViewportClient_Editor.h"

FWeaponEditorViewportClient_Editor::FWeaponEditorViewportClient_Editor(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene, TWeakPtr<FWeaponEditor> InWeaponEditor)
	: FWeaponEditorViewportClient(InModeTools, InPreviewScene, InWeaponEditor)
{
	SetViewLocation(FVector(30.f, 100.f, 160.f));
	SetViewRotation(FRotator(-22.5f, -90.0f, 0.0f));
}

void FWeaponEditorViewportClient_Editor::Tick(float DeltaSeconds)
{
	FWeaponEditorViewportClient::Tick(DeltaSeconds);
}
 