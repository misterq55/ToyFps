#include "SWeaponEditorViewport.h"
#include "WeaponSystem/WeaponEditor/WeaponEditor.h"
#include "WeaponSystem/WeaponEditor/WeaponEditorViewportClient/WeaponEditorViewportClient_Editor.h"
#include "WeaponSystem/WeaponEditor/WeaponEditorViewportClient/WeaponEditorViewportClient_FirstPerson.h"
#include "PreviewScene.h"

void SWeaponEditorViewport::Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor, EWeaponEditorViewport InViewportType, FPreviewScene* InPreviewScene)
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
	case EWeaponEditorViewport::EditorViewport:
		EditorViewportClient = MakeShareable(new FWeaponEditorViewportClient_Editor(nullptr, WeaponEditorPreviewScene));
		break;

	case EWeaponEditorViewport::FirstPersonViewport:
		EditorViewportClient = MakeShareable(new FWeaponEditorViewportClient_FirstPerson(nullptr, WeaponEditorPreviewScene));
		break;

	default:
		EditorViewportClient = MakeShareable(new FWeaponEditorViewportClient(nullptr, WeaponEditorPreviewScene));
		break;
	};

	return EditorViewportClient.ToSharedRef();
}
