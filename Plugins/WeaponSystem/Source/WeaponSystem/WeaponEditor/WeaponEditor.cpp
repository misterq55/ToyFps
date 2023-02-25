// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "IDetailsView.h"
#include "WeaponSystem/WeaponEditor/SWeaponEditorViewport/SWeaponEditorViewport.h"
#include "PreviewScene.h"

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

	WeaponEditorPreviewScene = MakeShareable(new FPreviewScene());
	EditorViewport = SNew(SWeaponEditorViewport, SharedThis(this), SWeaponEditorViewport::EWeaponEditorViewport::EditorViewport, WeaponEditorPreviewScene.Get());
	FirstPersonViewport = SNew(SWeaponEditorViewport, SharedThis(this), SWeaponEditorViewport::EWeaponEditorViewport::FirstPersonViewport, WeaponEditorPreviewScene.Get());

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
							->AddTab(TEXT("Empty"), ETabState::OpenedTab)
						)
					)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.2f)
						->AddTab(TEXT("DetailsView"), ETabState::OpenedTab)
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

void FWeaponEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	InTabManager->RegisterTabSpawner(TEXT("DetailsView"), FOnSpawnTab::CreateSP(this, &FWeaponEditor::SpawnTab_Details));
	InTabManager->RegisterTabSpawner(TEXT("EditorViewport"), FOnSpawnTab::CreateSP(this, &FWeaponEditor::SpawnTab_EditorViewport));
	InTabManager->RegisterTabSpawner(TEXT("FirstPersonViewport"), FOnSpawnTab::CreateSP(this, &FWeaponEditor::SpawnTab_FirstPersonViewport));
}

void FWeaponEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(TEXT("DetailsView"));
	InTabManager->UnregisterTabSpawner(TEXT("EditorViewport"));
	InTabManager->UnregisterTabSpawner(TEXT("FirstPersonViewport"));
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
