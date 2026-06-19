#pragma once

#include "PropertyCustomizationHelpers.h"

class SWeaponEditorClassProperty : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeaponEditorClassProperty)
		: _MetaClass(UObject::StaticClass())
		, _RequiredInterface(nullptr)
		, _AllowAbstract(false)
		, _IsBlueprintBaseOnly(false)
		, _AllowNone(true)
		, _HideViewOptions(false)
		, _ShowDisplayNames(false)
		, _ShowTreeView(false)
	{}

		/** The name to the class */
		SLATE_ATTRIBUTE(FText, ClassName);
		/** The meta class that the selected class must be a child-of (required) */
		SLATE_ARGUMENT(const UClass*, MetaClass)
		/** An interface that the selected class must implement (optional) */
		SLATE_ARGUMENT(const UClass*, RequiredInterface)
		/** Whether or not abstract classes are allowed (optional) */
		SLATE_ARGUMENT(bool, AllowAbstract)
		/** Should only base blueprints be displayed? (optional) */
		SLATE_ARGUMENT(bool, IsBlueprintBaseOnly)
		/** Should we be able to select "None" as a class? (optional) */
		SLATE_ARGUMENT(bool, AllowNone)
		/** Show the View Options part of the class picker dialog*/
		SLATE_ARGUMENT(bool, HideViewOptions)
		/** true to show class display names rather than their native names, false otherwise */
		SLATE_ARGUMENT(bool, ShowDisplayNames)
		/** Show the class picker as a tree view rather than a list*/
		SLATE_ARGUMENT(bool, ShowTreeView)
		/** Attribute used to get the currently selected class (required) */
		SLATE_ATTRIBUTE(const UClass*, SelectedClass)
		/** Delegate used to set the currently selected class (required) */
		SLATE_EVENT(FOnSetClass, OnSetClass)
		/** Called when the button is clicked */
		SLATE_EVENT(FOnClicked, OnClicked)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
};