// Fill out your copyright notice in the Description page of Project Settings.


#include "ListEntry/PropertyListEntry.h"

#include "Base/PropertyEntity.h"
#include "Components/TextBlock.h"

void UPropertyListEntry::SetPropertyEntity(UPropertyEntity* InProperty)
{
	Super::SetPropertyEntity(InProperty);

	Text_DisplayName->SetText(InProperty->GetDisplayName());
}
