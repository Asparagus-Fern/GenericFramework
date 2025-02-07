// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/WidgetEntity.h"

#include "WidgetManager.h"
#include "Manager/ManagerStatics.h"


bool FDisplayWidget::HasValidWidget() const
{
	return (bUseClass && IsValid(WidgetClass)) || (!bUseClass && IsValid(WidgetRef));
}

UUserWidgetBase* FDisplayWidget::GetWidget()
{
	return GetWidget<UUserWidgetBase>();
}

void UWidgetEntity::NativeOnCreate()
{
	IStateInterface::NativeOnCreate();
}

void UWidgetEntity::NativeOnDestroy()
{
	IStateInterface::NativeOnDestroy();
}

void UWidgetEntity::OpenEntityWidget_Implementation()
{
	IWidgetEntityInterface::OpenEntityWidget_Implementation();

	if (UUserWidgetBase* Widget = GetWidget())
	{
		if (!Widget->WidgetEntity.IsValid())
		{
			Widget->WidgetEntity = this;
		}

		OnEntityWidgetInitialized();
	}
}

void UWidgetEntity::CloseEntityWidget_Implementation()
{
	IWidgetEntityInterface::CloseEntityWidget_Implementation();
	OnEntityWidgetDeinitialized();
}

void UWidgetEntity::OnEntityWidgetInitialized()
{
	if (UWidgetManager* WidgetManager = GetManager<UWidgetManager>())
	{
		WidgetManager->OpenUserWidget(GetWidget());
	}
}

void UWidgetEntity::OnEntityWidgetDeinitialized()
{
	if (UWidgetManager* WidgetManager = GetManager<UWidgetManager>())
	{
		WidgetManager->CloseUserWidget(GetWidget(), false);
	}
}

UUserWidgetBase* UWidgetEntity::GetWidgetByClass(TSubclassOf<UUserWidgetBase> InClass)
{
	ensure(InClass);
	return DisplayWidget.GetWidget<UUserWidgetBase>();
}

UUserWidgetBase* UWidgetEntity::GetWidget()
{
	return DisplayWidget.GetWidget<UUserWidgetBase>();
}
