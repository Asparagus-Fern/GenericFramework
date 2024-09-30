// Fill out your copyright notice in the Description page of Project Settings.


#include "Collection/PropertyCollection.h"

void UPropertyCollection::AddProperty(UPropertyEntity* InProperty)
{
#if !UE_BUILD_SHIPPING
	ensureAlwaysMsgf(InProperty->GetPropertyOwner() == nullptr, TEXT("This setting already has a parent!"));
	ensureAlwaysMsgf(!ChildProperties.Contains(InProperty), TEXT("This collection already includes this setting!"));
#endif

	ChildProperties.Add(InProperty);
	InProperty->SetPropertyOwner(this);

	if (Context)
	{
		InProperty->Initialize(Context);
	}
}
