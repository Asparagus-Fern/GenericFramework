// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MenuStyle.h"

#include "Entity/MenuEntity.h"

void UMenuStyle::ConstructMenuStyle_Implementation()
{
}

void UMenuStyle::NativeConstructMenuStyle()
{
	ConstructMenuStyle();
}

UMenuEntityBase* UMenuStyle::GetMenuEntityBase() const
{
	if (WidgetEntity.IsValid())
	{
		return Cast<UMenuEntityBase>(WidgetEntity);
	}
	return nullptr;
}
