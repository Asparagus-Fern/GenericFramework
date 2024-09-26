// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/PropertyEntity.h"

FName UPropertyEntity::GetPropertyName() const
{
	return PropertyName;
}

void UPropertyEntity::SetPropertyName(const FName InPropertyName)
{
	PropertyName = InPropertyName;
}

FText UPropertyEntity::GetDisplayName() const
{
	return DisplayName;
}

void UPropertyEntity::SetDisplayName(const FText& InDisplayName)
{
	DisplayName = InDisplayName;
}

FText UPropertyEntity::GetDescriptionText() const
{
	return DescriptionText;
}

void UPropertyEntity::SetDescriptionText(const FText& InDescriptionText)
{
	DescriptionText = InDescriptionText;
}
