// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Widget/ListEntry/PropertyListEntry.h"

#include "Base/PropertyEntity.h"
#include "Components/TextBlock.h"

void UPropertyListEntry::SetPropertyEntity(UPropertyEntity* InProperty)
{
	Super::SetPropertyEntity(InProperty);

	if (Text_DisplayName)
	{
		Text_DisplayName->SetText(InProperty->GetDisplayName());
	}
}
