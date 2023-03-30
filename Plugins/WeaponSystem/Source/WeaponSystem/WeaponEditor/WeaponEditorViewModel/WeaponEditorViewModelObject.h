// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class FViewModelCrossHairObject
{
	DECLARE_DELEGATE_OneParam(FOnSetCrossHair, class UWeaponCrossHairWidget*);
	DECLARE_DELEGATE_OneParam(FOnSetCenterPivot, FVector2D);

public:
	FViewModelCrossHairObject() {}
	~FViewModelCrossHairObject() {}

	void SetCrossHair(class UWeaponCrossHairWidget* InCrossHair) {
		CrossHair = InCrossHair;
		OnSetCrossHair.ExecuteIfBound(CrossHair);
	}

	class UWeaponCrossHairWidget* GetCrossHair() {
		return CrossHair;
	}

	void SetCenterPivot(FVector2D InCenterPivot) {
		CenterPivot = InCenterPivot;
		OnSetCenterPivot.ExecuteIfBound(CenterPivot);
	}

	FVector2D GetCenterPivot() {
		return CenterPivot;
	}

public:
	FOnSetCrossHair OnSetCrossHair;
	FOnSetCenterPivot OnSetCenterPivot;

private:
	class UWeaponCrossHairWidget* CrossHair = nullptr;
	FVector2D CenterPivot;
};

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