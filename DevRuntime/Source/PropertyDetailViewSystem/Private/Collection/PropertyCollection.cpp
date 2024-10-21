// Fill out your copyright notice in the Description page of Project Settings.


#include "Collection/PropertyCollection.h"

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
		DLOG(DLogProperty, Error, TEXT("InProperty Is NULL"))
		return;
	}

#if !UE_BUILD_SHIPPING
	ensureAlwaysMsgf(InProperty->GetOwnerProperty() == nullptr, TEXT("This Property Already Has A Parent!"));
	ensureAlwaysMsgf(!ChildProperties.Contains(InProperty), TEXT("This Collection Already Includes This Property!"));
#endif

	/* 添加并设置该属性的Owner */
	ChildProperties.Add(InProperty);
	InProperty->SetOwnerProperty(this);

	/* 如果该属性Context为空，使用当前集合的Context对属性进行初始化 */
	if (Context && !InProperty->IsContextValid())
	{
		InProperty->Initialize(Context);
	}
	/* 属性初始化 */
	else if (InProperty->IsContextValid())
	{
		InProperty->Initialize();
	}
}
