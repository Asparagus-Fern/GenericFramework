// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Item/BackpackItemComponent.h"

#include "BackpackManager.h"
#include "Manager/ManagerProxy.h"

UBackpackItemComponent::UBackpackItemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBackpackItemComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UBackpackManager* BackpackManager = UManagerProxy::Get()->GetManager<UBackpackManager>())
	{
		BackpackManager->RegisterBackpackItem(this);
	}
}

void UBackpackItemComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (UBackpackManager* BackpackManager = UManagerProxy::Get()->GetManager<UBackpackManager>())
	{
		BackpackManager->UnRegisterBackpackItem(this);
	}
}
