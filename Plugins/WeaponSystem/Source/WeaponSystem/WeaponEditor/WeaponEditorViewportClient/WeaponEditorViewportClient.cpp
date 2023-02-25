#include "WeaponEditorViewportClient.h"

FWeaponEditorViewportClient::FWeaponEditorViewportClient(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene)
	: FEditorViewportClient(InModeTools, InPreviewScene, nullptr)
{
}

void FWeaponEditorViewportClient::Tick(float DeltaSeconds)
{
}
