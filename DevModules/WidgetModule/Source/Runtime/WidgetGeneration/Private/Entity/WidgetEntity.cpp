// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/WidgetEntity.h"

#include "WidgetManager.h"
#include "Manager/ManagerStatics.h"

void UWidgetEntity::OnCreate_Implementation()
{
	IStateInterface::OnCreate_Implementation();
}

void UWidgetEntity::OnDestroy_Implementation()
{
	IStateInterface::OnDestroy_Implementation();
}

void UWidgetEntity::OpenEntityWidget_Implementation()
{
	IWidgetEntityInterface::OpenEntityWidget_Implementation();

	if (UWidgetManager* WidgetManager = GetManager<UWidgetManager>())
	{
		WidgetManager->OpenUserWidget(GetWidget());
	}
}

void UWidgetEntity::CloseEntityWidget_Implementation()
{
	IWidgetEntityInterface::CloseEntityWidget_Implementation();

	if (UWidgetManager* WidgetManager = GetManager<UWidgetManager>())
	{
		WidgetManager->CloseUserWidget(GetWidget(), false);
	}
}

bool UWidgetEntity::HasValidWidget() const
{
	return (bUseClass && IsValid(WidgetClass)) || (!bUseClass && IsValid(WidgetRef));
}

UUserWidgetBase* UWidgetEntity::GetWidgetByClass(TSubclassOf<UUserWidgetBase> InClass)
{
	ensure(InClass);
	return GetWidget<UUserWidgetBase>();
}

UUserWidgetBase* UWidgetEntity::GetWidget()
{
	return GetWidget<UUserWidgetBase>();
}
