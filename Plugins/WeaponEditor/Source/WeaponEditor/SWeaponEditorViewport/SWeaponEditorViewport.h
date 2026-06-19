#pragma once

#include "SEditorViewport.h"

class FWeaponEditor;
class FEditorViewportClient;
class FWeaponEditorViewportClient;
class FPreviewScene;

class SWeaponEditorViewport : public SEditorViewport
{
public:
	enum E_TFWeaponEditorViewport
	{
		EditorViewport,
		FirstPersonViewport,
	};

public:
	SLATE_BEGIN_ARGS(SWeaponEditorViewport) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor, E_TFWeaponEditorViewport InViewportType, FPreviewScene* InPreviewScene);
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

private:
	TWeakPtr<FWeaponEditor> WeaponEditor;
	TSharedPtr<FWeaponEditorViewportClient> EditorViewportClient;
	E_TFWeaponEditorViewport ViewportType;
	FPreviewScene* WeaponEditorPreviewScene;
};