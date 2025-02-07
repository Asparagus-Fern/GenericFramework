// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/MenuGroupEntity.h"

#include "InteractableWidgetEntityGroup.h"
#include "WidgetEntityManager.h"
#include "Collection/MenuCollection.h"
#include "Manager/ManagerStatics.h"
#include "Menu/MenuContainer.h"
#include "Menu/MenuStyle.h"

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
	
	const TArray<UMenuEntityBase*> Children = GetChildrenEntities();
	
	/* Create Entity Group */
	if (!EntityGroup)
	{
		EntityGroup = NewObject<UInteractableWidgetEntityGroup>(this);
		EntityGroup->NativeOnCreate();
	}
	
	/* Add Children To Entity Group */
	EntityGroup->AddEntities(Children);

	/* Open The Container Widget And Add All Child Widget In It */
	if (UWidgetManager* WidgetManager = GetManager<UWidgetManager>())
	{
		if (ChildWidget.HasValidWidget())
		{
			WidgetManager->OpenUserWidget(ChildWidget.GetWidget());
		}
	}

	/* Register Children Entity */
	if (UWidgetEntityManager* WidgetEntityManager = GetManager<UWidgetEntityManager>())
	{
		WidgetEntityManager->RegisterWidgetEntity(Children);
	}
	
	/* Add Children Entity Widget In Group Entity  Widget (If Exist) */
	if (UMenuContainer* MenuContainer = Cast<UMenuContainer>(ChildWidget.GetWidget()))
	{
		for (int32 It = 0; It < Children.Num(); It++)
		{
			if (UMenuStyle* MenuStyle = Cast<UMenuStyle>(Children[It]->GetWidget()))
			{
				MenuContainer->NativeConstructMenuContainer(MenuStyle, It);
			}
		}

		MenuContainer->NativePostConstructMenuContainer();
	}
}

void UMenuGroupEntity::OnInactived_Implementation()
{
	Super::OnInactived_Implementation();

	/* Close All Child Widget And Remove It From Parent Slot */
	const TArray<UMenuEntityBase*> Children = GetChildrenEntities();
	for (auto& Child : Children)
	{
		Child->NativeOnInactived();
	}
	
	EntityGroup->DeselectAll();
	
	/* Unregister Children Entity */
	if (UWidgetEntityManager* WidgetEntityManager = GetManager<UWidgetEntityManager>())
	{
		WidgetEntityManager->UnRegisterWidgetEntity(Children);
	}
	
	/* Close The Container Widget */
	if (UWidgetManager* WidgetManager = GetManager<UWidgetManager>())
	{
		if (ChildWidget.HasValidWidget())
		{
			WidgetManager->CloseUserWidget(ChildWidget.GetWidget());
		}
	}

	EntityGroup->NativeOnDestroy();
	EntityGroup->MarkAsGarbage();
	EntityGroup = nullptr;
}

TArray<UMenuEntityBase*> UMenuGroupEntity::GetChildrenEntities() const
{
	if (Collection.IsValid())
	{
		return Collection->GetDirectChildMenuEntities(MenuTag);
	}
	else
	{
		return TArray<UMenuEntityBase*>{};
	}
}
