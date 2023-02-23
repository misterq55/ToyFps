// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "IDetailsView.h"

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
				FTabManager::NewStack()
				->SetSizeCoefficient(0.2f)
				->AddTab(TEXT("DetailsView"), ETabState::OpenedTab)
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
}

void FWeaponEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(TEXT("DetailsView"));
}

TSharedRef<SDockTab> FWeaponEditor::SpawnTab_Details(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		[
			DetailsView.ToSharedRef()
		];
}