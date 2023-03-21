// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WeaponEditorViewModel.generated.h"

/**
 * 
 */

class FViewModelAssetObject
{
public:
	FViewModelAssetObject() {}
	FViewModelAssetObject(FString InAssetPath, std::function<void(const FAssetData& AssetData)> InAssetChangeLambda) {
		SetAssetPath(InAssetPath);
		OnChangeAssetLambda = InAssetChangeLambda;
	}

	~FViewModelAssetObject() {}

public:
	FString GetAssetPath() const { return AssetPath; }
	void SetAssetPath(FString InAssetPath) { AssetPath = InAssetPath; }
	void OnChangeAsset(const FAssetData& AssetData) {
		if (OnChangeAssetLambda)
		{
			OnChangeAssetLambda(AssetData);
			SetAssetPath(AssetData.GetObjectPathString());
		}
	}

private:
	FString AssetPath;
	std::function<void(const FAssetData& AssetData)> OnChangeAssetLambda;
};

class FViewModelAbilityObject
{
public:
	FViewModelAbilityObject() {}

	FViewModelAbilityObject(const UClass* SelectedClass, std::function<void(const UClass* SelectedClass)> InOnSetClassLambda, std::function<void()> InOnClickAbilityLambda) {
		AbilityClass = MakeWeakObjectPtr(SelectedClass);
		OnSetClassLambda = InOnSetClassLambda;
		OnClickAbilityLambda = InOnClickAbilityLambda;
	}

	~FViewModelAbilityObject() {}

public:
	const UClass* OnGetAbilityClass() const
	{
		return AbilityClass.Get();
	}

	void OnSetAbilityClass(const UClass* SelectedClass)
	{
		OnSetClassLambda(SelectedClass);
		AbilityClass = MakeWeakObjectPtr(SelectedClass);
	}

	FReply ClickedOnRunAbility() {
		
		if (OnClickAbilityLambda)
			OnClickAbilityLambda();

		return FReply::Handled();
	}
private:
	TWeakObjectPtr<const UClass> AbilityClass;
	std::function<void(const UClass* SelectedClass)> OnSetClassLambda;
	std::function<void()> OnClickAbilityLambda;
};

UCLASS()
class WEAPONSYSTEM_API UWeaponEditorViewModel : public UObject
{
	GENERATED_BODY()
	
public:
	void SetEditorWorld(UWorld* InEditorWorld) { EditorWorld = InEditorWorld; }
	bool InitializeViewModel(const TArray<UObject*>& InObjects);

	TObjectPtr<class AEditorCharacter> GetEditorCharacter() {
		return EditorCharacter;
	}

	TSharedPtr<FViewModelAssetObject> GetViewModelAssetObject(const FString& InKey);
	TSharedPtr<FViewModelAbilityObject> GetViewModelAbilityObject(const FString& InKey);

private:
	UWorld* EditorWorld = nullptr;
	TObjectPtr<class AEditorCharacter> EditorCharacter = nullptr;

	TMap<FString, TSharedPtr<FViewModelAssetObject>> ViewModelAssetObject;
	TMap<FString, TSharedPtr<FViewModelAbilityObject>> ViewModelAbilityObject;

	TObjectPtr<class UWeaponAsset> CurrentWeaponAsset;
};
