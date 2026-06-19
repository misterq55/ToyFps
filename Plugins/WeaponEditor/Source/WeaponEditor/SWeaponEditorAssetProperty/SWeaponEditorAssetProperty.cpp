#include "SWeaponEditorAssetProperty.h"
#include "Widgets/Text/STextBlock.h"

void SWeaponEditorAssetProperty::Construct(const FArguments& InArgs)
{
	ChildSlot
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Top)
			[
				SNew(SBox)
				.Padding(FMargin(4.0f, 0.0f, 0.0f, 0.0f))
				.WidthOverride(200.f)
				.HeightOverride(50.f)
				[
					SNew(SBorder)
					[
						SNew(STextBlock)
						.Text(InArgs._ObjectName)
					]
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Top)
			[
				SNew(SBox)
				.Padding(FMargin(4.0f, 0.0f, 0.0f, 0.0f))
				.WidthOverride(200.f)
				.HeightOverride(50.f)
				[
					SNew(SBorder)
					[
						SNew(SObjectPropertyEntryBox)
						.DisplayBrowse(InArgs._DisplayBrowse)
						.DisplayThumbnail(InArgs._DisplayThumbnail)
						.AllowedClass(InArgs._AllowedClass)
						.EnableContentPicker(InArgs._EnableContentPicker)
						.ThumbnailPool(InArgs._ThumbnailPool)
						.ObjectPath(InArgs._ObjectPath)
						.OnObjectChanged(InArgs._OnObjectChanged)
					]
				]
			]
		];
}