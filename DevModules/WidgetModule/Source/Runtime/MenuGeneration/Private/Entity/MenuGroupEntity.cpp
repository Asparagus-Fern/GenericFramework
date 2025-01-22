// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/MenuGroupEntity.h"

#include "InteractableWidgetEntityGroup.h"
#include "Collection/MenuCollection.h"

UMenuGroupEntity::UMenuGroupEntity(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMenuGroupEntity::Initialize()
{
	Super::Initialize();
}

void UMenuGroupEntity::DeInitialize()
{
	Super::DeInitialize();
}

void UMenuGroupEntity::OnActived_Implementation()
{
	Super::OnActived_Implementation();

	if (!EntityGroup)
	{
		EntityGroup = NewObject<UInteractableWidgetEntityGroup>(this);
	}

	IWidgetEntityInterface::Execute_OpenEntityWidget(this);

	const TArray<UMenuEntityBase*> Children = GetChildrenEntities();
	for (auto& Child : Children)
	{
		IWidgetEntityInterface::Execute_OpenEntityWidget(Child);
	}

	EntityGroup->AddEntities(Children);
}

void UMenuGroupEntity::OnInactived_Implementation()
{
	Super::OnInactived_Implementation();

	const TArray<UMenuEntityBase*> Children = GetChildrenEntities();
	for (auto& Child : Children)
	{
		Child->NativeOnInactived();
		IWidgetEntityInterface::Execute_CloseEntityWidget(Child);
	}

	IWidgetEntityInterface::Execute_CloseEntityWidget(this);
}

TArray<UMenuEntityBase*> UMenuGroupEntity::GetChildrenEntities() const
{
	if (Collection.IsValid())
	{
		return Collection.Pin()->GetDirectChildMenuEntities(MenuTag);
	}
	else
	{
		return TArray<UMenuEntityBase*>{};
	}
}
