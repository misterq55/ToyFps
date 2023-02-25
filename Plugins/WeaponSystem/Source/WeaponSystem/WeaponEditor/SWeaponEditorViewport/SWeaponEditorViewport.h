#include "SEditorViewport.h"
#include "EditorViewportClient.h"

class FWeaponEditor;
class FWeaponEditorViewportClient;
class FPreviewScene;

class SWeaponEditorViewport : public SEditorViewport
{
public:
	enum EWeaponEditorViewport
	{
		EditorViewport,
		FirstPersonViewport,
	};

public:
	SLATE_BEGIN_ARGS(SWeaponEditorViewport) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, TSharedPtr<FWeaponEditor> InSpriteEditor, EWeaponEditorViewport InViewportType, FPreviewScene* InPreviewScene);
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

private:
	TWeakPtr<FWeaponEditor> WeaponEditor;
	TSharedPtr<FWeaponEditorViewportClient> EditorViewportClient;
	EWeaponEditorViewport ViewportType;
	FPreviewScene* WeaponEditorPreviewScene;
};