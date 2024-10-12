// Fill out your copyright notice in the Description page of Project Settings.


#include "DataSource/PropertySourceHandle.h"

#include "Collection/PropertyCollection.h"

void UPropertySourceHandle::Initialize()
{
	PropertyCollection = NewObject<UPropertyCollection>(this);
	InitializePropertyCollection(PropertyCollection);
}

UPropertyCollection* UPropertySourceHandle::GetPropertyCollection() const
{
	return PropertyCollection;
}
