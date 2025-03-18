// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/WidgetEntity.h"

#include "WidgetManager.h"
#include "Manager/ManagerStatics.h"


bool FDisplayWidget::HasValidWidget() const
{
	return (bUseClass && IsValid(WidgetClass)) || (!bUseClass && IsValid(WidgetRef));
}

UUserWidgetBase* FDisplayWidget::GetWidget() const
{
	if (!HasValidWidget())
	{
		DLOG(DLogUI, Warning, TEXT("Entity Has No Widget"))
		return nullptr;
	}

	UUserWidgetBase* Result = nullptr;
	if (bUseClass)
	{
		Result = CreateWidget<UUserWidgetBase>(GetManager<UWidgetManager>()->GetWorld(), WidgetClass);
	}
	else
	{
		Result = WidgetRef;
	}

	return Result;
}

void UWidgetEntity::NativeOnCreate()
{
	IStateInterface::NativeOnCreate();
	WidgetInternal = DisplayWidget.GetWidget();
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

UUserWidgetBase* UWidgetEntity::GetWidgetByClass(const TSubclassOf<UUserWidgetBase>& InClass)
{
	ensure(InClass);
	return GetWidget<UUserWidgetBase>();
}

UUserWidgetBase* UWidgetEntity::GetWidget() const
{
	return WidgetInternal.Get();
}

void UWidgetEntity::SetWidget(UUserWidgetBase* InWidget)
{
	WidgetInternal = InWidget;
}
