// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Base/PropertyCollection.h"

#include "Debug/DebugType.h"

TArray<UPropertyEntity*> UPropertyCollection::GetChildProperties()
{
	return ChildProperties;
}

TArray<UPropertyCollection*> UPropertyCollection::GetChildCollections() const
{
	TArray<UPropertyCollection*> Collections;

	for (auto ChlidProperty : ChildProperties)
	{
		if (UPropertyCollection* ChildCollection = Cast<UPropertyCollection>(ChlidProperty))
		{
			Collections.Add(ChildCollection);
		}
	}

	return Collections;
}

void UPropertyCollection::AddProperty(UPropertyEntity* InProperty)
{
	if (!ensureAlways(InProperty))
	{
		GenericLOG(GenericLogProperty, Error, TEXT("InProperty Is NULL"))
		return;
	}

#if !UE_BUILD_SHIPPING
	ensureAlwaysMsgf(InProperty->GetOwnerProperty() == nullptr, TEXT("This Property Already Has A Parent!"));
	ensureAlwaysMsgf(!ChildProperties.Contains(InProperty), TEXT("This Collection Already Includes This Property!"));
#endif

	/* 添加并设置该属性的Owner */
	ChildProperties.Add(InProperty);
	InProperty->SetOwnerProperty(this);
	InProperty->Initialize(Context);
}
