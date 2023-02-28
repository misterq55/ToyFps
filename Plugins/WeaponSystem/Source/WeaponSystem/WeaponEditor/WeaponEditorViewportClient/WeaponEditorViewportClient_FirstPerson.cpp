#include "WeaponEditorViewportClient_FirstPerson.h"
#include "WeaponSystem/WeaponEditor/WeaponEditor.h"
#include "WeaponSystem/Character/EditorCharacter.h"
#include "Camera/CameraComponent.h"
#include "InputCoreTypes.h"
#include "UnrealClient.h"

FWeaponEditorViewportClient_FirstPerson::FWeaponEditorViewportClient_FirstPerson(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene, TWeakPtr<FWeaponEditor> InWeaponEditor)
	: FWeaponEditorViewportClient(InModeTools, InPreviewScene, InWeaponEditor)
{
	Viewport->ViewportResizedEvent.AddRaw(this, &FWeaponEditorViewportClient_FirstPerson::OnViewportResize);
}

void FWeaponEditorViewportClient_FirstPerson::Tick(float DeltaSeconds)
{
	GetPreviewScene()->GetWorld()->Tick(ELevelTick::LEVELTICK_All, DeltaSeconds);

	AEditorCharacter *EditorCharacter = WeaponEditor.Pin()->GetEditorCharacter();

	FMinimalViewInfo ViewInfo;
	EditorCharacter->GetMainCamera()->GetCameraView(DeltaSeconds, ViewInfo);
	SetViewLocation(ViewInfo.Location);
	SetViewRotation(EditorCharacter->GetViewRotation());

	AspectRatio = ViewInfo.AspectRatio;

	FIntPoint ViewportSize = Viewport->GetSizeXY();
	Viewport->ViewportResizedEvent;
	Invalidate();
}

void FWeaponEditorViewportClient_FirstPerson::MouseMove(FViewport* InViewport, int32 x, int32 y)
{
	const bool RightMouseButtonDown = Viewport->KeyState(EKeys::RightMouseButton);

	/*if (!RightMouseButtonDown)
		return;

	int32 Temp = 0;*/

	if (RightMouseButtonDown)
	{
		int32 Temp = 0;
	}
}

FSceneView* FWeaponEditorViewportClient_FirstPerson::CalcSceneView(FSceneViewFamily* ViewFamily, const int32 StereoViewIndex)
{
	FSceneView* SceneView = FEditorViewportClient::CalcSceneView(ViewFamily, StereoViewIndex);
	SceneView->UnscaledViewRect;
	return SceneView;
}

void FWeaponEditorViewportClient_FirstPerson::OnViewportResize(FViewport* InViewport, uint32 InParams)
{
}
