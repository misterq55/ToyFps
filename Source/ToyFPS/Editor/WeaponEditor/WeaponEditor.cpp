// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponEditor.h"

void FWeaponEditor::InitEditor(const TArray<UObject*>& InObjects)
{
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
