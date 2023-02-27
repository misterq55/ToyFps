#include "WeaponEditorViewportClient_FirstPerson.h"
#include "WeaponSystem/WeaponEditor/WeaponEditor.h"
#include "WeaponSystem/Character/EditorCharacter.h"
#include "Camera/CameraComponent.h"

FWeaponEditorViewportClient_FirstPerson::FWeaponEditorViewportClient_FirstPerson(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene, TWeakPtr<FWeaponEditor> InWeaponEditor)
	: FWeaponEditorViewportClient(InModeTools, InPreviewScene, InWeaponEditor)
{
}

void FWeaponEditorViewportClient_FirstPerson::Tick(float DeltaSeconds)
{
	GetPreviewScene()->GetWorld()->Tick(ELevelTick::LEVELTICK_All, DeltaSeconds);

	AEditorCharacter *EditorCharacter = WeaponEditor.Pin()->GetEditorCharacter();

	FMinimalViewInfo ViewInfo;
	EditorCharacter->GetMainCamera()->GetCameraView(DeltaSeconds, ViewInfo);
	SetViewLocation(ViewInfo.Location);
	SetViewRotation(EditorCharacter->GetViewRotation());

	FWeaponEditorViewportClient::Tick(DeltaSeconds);
}
