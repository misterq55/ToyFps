#include "SWeaponEditorViewport.h"
#include "WeaponSystem/WeaponEditor/WeaponEditor.h"
#include "WeaponSystem/WeaponEditor/WeaponEditorViewportClient/WeaponEditorViewportClient_Editor.h"
#include "WeaponSystem/WeaponEditor/WeaponEditorViewportClient/WeaponEditorViewportClient_FirstPerson.h"
#include "PreviewScene.h"

void SWeaponEditorViewport::Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor, E_TFWeaponEditorViewport InViewportType, FPreviewScene* InPreviewScene)
{
	WeaponEditor = InSpriteEditor;
	ViewportType = InViewportType;
	WeaponEditorPreviewScene = InPreviewScene;
	SEditorViewport::Construct(SEditorViewport::FArguments());
}

TSharedRef<FEditorViewportClient> SWeaponEditorViewport::MakeEditorViewportClient()
{
	switch (ViewportType)
	{
	case E_TFWeaponEditorViewport::EditorViewport:
		EditorViewportClient = MakeShareable(new FWeaponEditorViewportClient_Editor(nullptr, WeaponEditorPreviewScene, WeaponEditor));
		break;

	case E_TFWeaponEditorViewport::FirstPersonViewport:
		EditorViewportClient = MakeShareable(new FWeaponEditorViewportClient_FirstPerson(nullptr, WeaponEditorPreviewScene, WeaponEditor));
		break;

	default:
		EditorViewportClient = MakeShareable(new FWeaponEditorViewportClient(nullptr, WeaponEditorPreviewScene, WeaponEditor));
		break;
	};

	return EditorViewportClient.ToSharedRef();
}
