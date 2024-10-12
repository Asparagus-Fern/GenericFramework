// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ListView/PropertyListView.h"

#include "Base/PropertyEntity.h"
#include "Widget/PropertyVisualData.h"
#include "Widget/ListEntry/PropertyListEntryBase.h"

#if WITH_EDITOR
#include "Editor/WidgetCompilerLog.h"
#endif

#define LOCTEXT_NAMESPACE "PropertyDetailViewSystem"

#if WITH_EDITOR

void UPropertyListView::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	// Super::ValidateCompiledDefaults(CompileLog);

	if (!VisualData)
	{
		CompileLog.Error(FText::Format(LOCTEXT("Error_PropertyListView_MissingVisualData", "{0} has no VisualData specified."), FText::FromString(GetName())));
	}
}

#endif

UUserWidget& UPropertyListView::OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable)
{
	UPropertyEntity* PropertyItem = Cast<UPropertyEntity>(Item);
	TSubclassOf<UPropertyListEntryBase> PropertyEntryClass = TSubclassOf<UPropertyListEntryBase>(DesiredEntryClass);

	if (VisualData)
	{ 
		if (const TSubclassOf<UPropertyListEntryBase> EntryClass = VisualData->GetEntryForProperty(PropertyItem))
		{
			PropertyEntryClass = EntryClass;
		}
	}

	UPropertyListEntryBase& EntryWidget = GenerateTypedEntry<UPropertyListEntryBase>(PropertyEntryClass, OwnerTable);

	if (!IsDesignTime())
	{
		EntryWidget.SetPropertyEntity(PropertyItem);
	}

	return EntryWidget;
}

bool UPropertyListView::OnIsSelectableOrNavigableInternal(UObject* FirstSelectedItem)
{
	return Super::OnIsSelectableOrNavigableInternal(FirstSelectedItem);
}

#undef LOCTEXT_NAMESPACE
