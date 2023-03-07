// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "IDetailsView.h"
#include "WeaponSystem/WeaponEditor/SWeaponEditorViewport/SWeaponEditorViewport.h"
#include "WeaponSystem/WeaponEditor/SWeaponInfo/SWeaponInfo.h"
#include "WeaponSystem/WeaponEditor/SWeaponAnimationAssets/SWeaponAnimationAssets.h"
#include "WeaponSystem/WeaponEditor/SWeaponAbilities/SWeaponAbilities.h"
#include "AdvancedPreviewScene.h"
#include "WeaponSystem/Character/EditorCharacter.h"

void FWeaponEditor::InitEditor(const TArray<UObject*>& InObjects)
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);

	if (DetailsView.IsValid())
	{
		DetailsView->SetObjects(InObjects);
	}

	WeaponEditorPreviewScene = MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues()));

	EditorCharacter = WeaponEditorPreviewScene->GetWorld()->SpawnActor<AEditorCharacter>();
	EditorCharacter->SetWeaponAsset(InObjects[0]);
	EditorCharacter->SpawnWeaponActor();

	EditorViewport = SNew(SWeaponEditorViewport, SharedThis(this), SWeaponEditorViewport::EWeaponEditorViewport::EditorViewport, WeaponEditorPreviewScene.Get());
	FirstPersonViewport = SNew(SWeaponEditorViewport, SharedThis(this), SWeaponEditorViewport::EWeaponEditorViewport::FirstPersonViewport, WeaponEditorPreviewScene.Get());

	WeaponInfo = SNew(SWeaponInfo, SharedThis(this));
	WeaponAnimationAssets = SNew(SWeaponAnimationAssets, SharedThis(this));
	WeaponAbilities = SNew(SWeaponAbilities, SharedThis(this));

	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("WeaponEditor_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.8f)
					->SetHideTabWell(true)
				)
				->Split
				(
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Horizontal)
					->Split
					(
						FTabManager::NewSplitter()
						->SetOrientation(Orient_Vertical)
						->Split
						(
							FTabManager::NewSplitter()
							->SetOrientation(Orient_Horizontal)
							->Split
							(
								FTabManager::NewStack()
								->SetSizeCoefficient(0.2f)
								->AddTab(TEXT("EditorViewport"), ETabState::OpenedTab)
							)
							->Split
							(
								FTabManager::NewStack()
								->SetSizeCoefficient(0.2f)
								->AddTab(TEXT("FirstPersonViewport"), ETabState::OpenedTab)
							)
						)
						->Split
						(
							FTabManager::NewStack()
							->SetSizeCoefficient(0.2f)
							->AddTab(TEXT("WeaponAbilities"), ETabState::OpenedTab)
						)
					)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.2f)
						->AddTab(TEXT("WeaponInfo"), ETabState::OpenedTab)
						->AddTab(TEXT("AnimationAssets"), ETabState::OpenedTab)
						->SetForegroundTab(FName(TEXT("WeaponInfo")))

					)
				)
			)
		);

	FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone, {}, "WeaponEditor", Layout, true, true, InObjects);
}

FName FWeaponEditor::GetToolkitFName() const
{
	return FName(TEXT("WeaponEditor"));
}

FText FWeaponEditor::GetBaseToolkitName() const
{
	return FText(FText::FromString(TEXT("WeaponEditor")));
}

FString FWeaponEditor::GetWorldCentricTabPrefix() const
{
	return FString();
}

FLinearColor FWeaponEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

TObjectPtr<AEditorCharacter> FWeaponEditor::GetEditorCharacter()
{
	return EditorCharacter;
}

void FWeaponEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	InTabManager->RegisterTabSpawner(TEXT("DetailsView"), FOnSpawnTab::CreateSP(this, &FWeaponEditor::SpawnTab_Details));
	InTabManager->RegisterTabSpawner(TEXT("EditorViewport"), FOnSpawnTab::CreateSP(this, &FWeaponEditor::SpawnTab_EditorViewport));
	InTabManager->RegisterTabSpawner(TEXT("FirstPersonViewport"), FOnSpawnTab::CreateSP(this, &FWeaponEditor::SpawnTab_FirstPersonViewport));
	InTabManager->RegisterTabSpawner(TEXT("WeaponInfo"), FOnSpawnTab::CreateSP(this, &FWeaponEditor::SpawnTab_WeaponInfo));
	InTabManager->RegisterTabSpawner(TEXT("AnimationAssets"), FOnSpawnTab::CreateSP(this, &FWeaponEditor::SpawnTab_AnimationAssets));
	InTabManager->RegisterTabSpawner(TEXT("WeaponAbilities"), FOnSpawnTab::CreateSP(this, &FWeaponEditor::SpawnTab_WeaponAbilities));

}

void FWeaponEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(TEXT("DetailsView"));
	InTabManager->UnregisterTabSpawner(TEXT("EditorViewport"));
	InTabManager->UnregisterTabSpawner(TEXT("FirstPersonViewport"));
	InTabManager->UnregisterTabSpawner(TEXT("WeaponInfo"));
	InTabManager->UnregisterTabSpawner(TEXT("AnimationAssets"));
	InTabManager->UnregisterTabSpawner(TEXT("WeaponAbilities"));
}

TSharedRef<SDockTab> FWeaponEditor::SpawnTab_Details(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		[
			DetailsView.ToSharedRef()
		];
}

TSharedRef<SDockTab> FWeaponEditor::SpawnTab_EditorViewport(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		[
			EditorViewport.ToSharedRef()
		];
}

TSharedRef<SDockTab> FWeaponEditor::SpawnTab_FirstPersonViewport(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		[
			FirstPersonViewport.ToSharedRef()
		];
}

TSharedRef<SDockTab> FWeaponEditor::SpawnTab_WeaponInfo(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		[
			WeaponInfo.ToSharedRef()
		];
}

TSharedRef<SDockTab> FWeaponEditor::SpawnTab_AnimationAssets(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		[
			WeaponAnimationAssets.ToSharedRef()
		];
}

TSharedRef<SDockTab> FWeaponEditor::SpawnTab_WeaponAbilities(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		[
			WeaponAbilities.ToSharedRef()
		];
}

