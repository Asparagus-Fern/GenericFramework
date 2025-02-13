// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/WidgetEntity.h"

#include "WidgetManager.h"
#include "Manager/ManagerStatics.h"


bool FDisplayWidget::HasValidWidget() const
{
	return IsValid(WidgetInternal) || (bUseClass && IsValid(WidgetClass)) || (!bUseClass && IsValid(WidgetRef));
}

UUserWidgetBase* FDisplayWidget::GetWidget()
{
	return GetWidget<UUserWidgetBase>();
}

void FDisplayWidget::SetWidget(UUserWidgetBase* InWidget)
{
	if (!IsValid(InWidget))
	{
		DLOG(DLogUI, Warning, TEXT("InWidget Is InValid"))
		return;
	}

	if (InWidget != WidgetInternal)
	{
		WidgetInternal = InWidget;
	}
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
		Widget->SetWidgetEntity(this);
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

void UWidgetEntity::SetWidget(UUserWidgetBase* InWidget)
{
	DisplayWidget.SetWidget(InWidget);
}
