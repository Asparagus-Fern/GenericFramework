// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Menu/MenuStyle.h"

#include "Entity/MenuEntity.h"

void UMenuStyle::ConstructMenuStyle_Implementation()
{
}

void UMenuStyle::NativeConstructMenuStyle()
{
	ConstructMenuStyle();
}

UMenuEntityBase* UMenuStyle::GetMenuEntityBase()
{
	return GetWidgetEntity<UMenuEntityBase>();
}
