// Copyright ChenTaiye 2025. All Rights Reserved.


#include "MenuCollectionCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "Collection/MenuCollection.h"

#define LOCTEXT_NAMESPACE "FMenuCollectionCustomization"

TSharedRef<IDetailCustomization> FMenuCollectionCustomization::MakeInstance()
{
	return MakeShareable(new FMenuCollectionCustomization);
}

void FMenuCollectionCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& MenuCollectionCategory = DetailBuilder.EditCategory("MenuCollection");

	ObjectsBeingCustomized.Empty();
	DetailBuilder.GetObjectsBeingCustomized(ObjectsBeingCustomized);

	MenuCollectionCategory
		.AddCustomRow(FText::GetEmpty())
		.WholeRowContent()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(SButton)
				.Text(FText::FromString("Generate"))
				.OnClicked(this, &FMenuCollectionCustomization::GenerateMenuEntities)
			]
		];
}

FReply FMenuCollectionCustomization::GenerateMenuEntities() const
{
	TArray<UObject*> StrongObjects;
	CopyFromWeakArray(StrongObjects, ObjectsBeingCustomized);

	for (const auto& StrongObject : StrongObjects)
	{
		if (UMenuCollection* MenuCollection = Cast<UMenuCollection>(StrongObject))
		{
			MenuCollection->GenerateMenu();
		}
	}

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
