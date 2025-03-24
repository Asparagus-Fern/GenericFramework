// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Entity/MenuEntity.h"

#include "WidgetManager.h"
#include "Manager/ManagerStatics.h"
#include "Menu/MenuStyle.h"

UMenuEntity::UMenuEntity(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMenuEntity::OnEntityWidgetInitialized()
{
	// Super::OnEntityWidgetInitialized();

	if (UWidgetManager* WidgetManager = GetManager<UWidgetManager>())
	{
		WidgetManager->ActiveWidget(GetWidget());
	}
}

void UMenuEntity::OnEntityWidgetDeinitialized()
{
	// Super::OnEntityWidgetDeinitialized();

	if (UWidgetManager* WidgetManager = GetManager<UWidgetManager>())
	{
		WidgetManager->InactiveWidget(GetWidget());
	}
}

void UMenuEntity::OnActived_Implementation()
{
	Super::OnActived_Implementation();
}

void UMenuEntity::OnInactived_Implementation()
{
	Super::OnInactived_Implementation();
}
