#pragma once

#include "CoreMinimal.h"
#include "WeaponEditorViewportClient.h"

class FViewport;
class FSceneView;
class FSceneViewFamily;

class FWeaponEditorViewportClient_FirstPerson : public FWeaponEditorViewportClient
{
public:
	FWeaponEditorViewportClient_FirstPerson(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene, TWeakPtr<FWeaponEditor> InWeaponEditor);
	virtual ~FWeaponEditorViewportClient_FirstPerson() {}

	virtual void Tick(float DeltaSeconds) override;
	virtual void MouseMove(FViewport* InViewport, int32 x, int32 y) override;
	virtual FSceneView* CalcSceneView(FSceneViewFamily* ViewFamily, const int32 StereoViewIndex = INDEX_NONE) override;
	void OnViewportResize(FViewport* InViewport, uint32 InParams);

};