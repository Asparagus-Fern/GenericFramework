// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UWidget/GenericListView.h"

void UGenericListView::SetEntryWidgetClass(TSubclassOf<UUserWidget> InClass)
{
	EntryWidgetClass = InClass;
}
