#include "SWeaponEditorClassProperty.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"

void SWeaponEditorClassProperty::Construct(const FArguments& InArgs)
{
	ChildSlot
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Top)
			[
				SNew(STextBlock)
				.Text(InArgs._ClassName)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Top)
			[
				SNew(SClassPropertyEntryBox)
				.MetaClass(InArgs._MetaClass)
				.SelectedClass(InArgs._SelectedClass)
				.OnSetClass(InArgs._OnSetClass)
			]

			+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Top)
				[
					SNew(SButton)
					.Text(FText::FromString(TEXT("Run Ability")))
					.OnClicked(InArgs._OnClicked)
				]
		];
}