#include "WeaponEditorViewportClient_FirstPerson.h"
#include "WeaponSystem/WeaponEditor/WeaponEditor.h"
#include "WeaponSystem/Character/EditorCharacter.h"
#include "Camera/CameraComponent.h"
#include "InputCoreTypes.h"
#include "UnrealClient.h"

#include "WeaponSystem/WeaponEditor/WeaponEditorViewModel/WeaponEditorViewModel.h"

FWeaponEditorViewportClient_FirstPerson::FWeaponEditorViewportClient_FirstPerson(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene, TWeakPtr<FWeaponEditor> InWeaponEditor)
	: FWeaponEditorViewportClient(InModeTools, InPreviewScene, InWeaponEditor)
{
	Viewport->ViewportResizedEvent.AddRaw(this, &FWeaponEditorViewportClient_FirstPerson::OnViewportResize);
}

void FWeaponEditorViewportClient_FirstPerson::Tick(float DeltaSeconds)
{
	// GetPreviewScene()->GetWorld()->Tick(ELevelTick::LEVELTICK_All, DeltaSeconds);

	if (!WeaponEditor.IsValid())
	{
		return;
	}
	
	AEditorCharacter *EditorCharacter = WeaponEditor.Pin()->GetEditorCharacter();

	if (!IsValid(EditorCharacter))
	{
		return;
	}

	FMinimalViewInfo ViewInfo;
	EditorCharacter->GetMainCamera()->GetCameraView(DeltaSeconds, ViewInfo);
	SetViewLocation(ViewInfo.Location);
	SetViewRotation(EditorCharacter->GetViewRotation());

	if (!WeaponEditor.IsValid())
	{
		return;
	}

	if (!WeaponEditor.Pin()->GetViewModel()->GetViewModelCrossHairObject().IsValid() || !IsValid(WeaponEditor.Pin()->GetViewModel()->GetViewModelCrossHairObject()->GetCrossHair()))
	{
		return;
	}
	
	//if (WeaponEditor.Pin()->GetViewModel()->GetViewModelCrossHairObject()->GetCrossHair() && WeaponEditor.Pin()->GetViewModel()->GetViewModelCrossHairObject()->GetCrossHair()->IsValidLowLevel())
	WeaponEditor.Pin()->GetViewModel()->GetViewModelCrossHairObject()->SetCenterPivot(FVector2D(Viewport->GetSizeXY().X / 2, Viewport->GetSizeXY().Y / 2));

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
	float Height = InViewport->GetSizeXY().Y;
	float Width = Height * AspectRatio;
	//InViewport->SetInitialSize(FIntPoint(Width, Height));

	// InViewport->MoveWindow

	/*if (WeaponEditor.IsValid() && WeaponEditor.Pin()->GetViewModel()->GetViewModelCrossHairObject().IsValid())
		WeaponEditor.Pin()->GetViewModel()->GetViewModelCrossHairObject()->SetCenterPivot(FVector2D(InViewport->GetSizeXY().X / 2, InViewport->GetSizeXY().Y / 2));*/

	/*InViewport->GetViewportFrame()->ResizeFrame(Width, Height, EWindowMode::Windowed);
	Invalidate();*/
}
