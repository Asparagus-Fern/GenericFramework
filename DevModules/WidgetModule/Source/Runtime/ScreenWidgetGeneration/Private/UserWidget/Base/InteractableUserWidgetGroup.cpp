// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/Base/InteractableUserWidgetGroup.h"

#include "Group/CommonButton.h"
#include "Group/CommonButtonGroup.h"
#include "UserWidget/Base/InteractableUserWidgetBase.h"

void UInteractableUserWidgetGroup::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!Panel_Content)
	{
		return;
	}

	InteractableUserWidgets.Reset();
	Panel_Content->ClearChildren();

	if (!IsDesignTime())
	{
		CommonButtonGroup = NewObject<UCommonButtonGroup>(this);
	}

	for (int i = 0; i < Num; i++)
	{
		if (UInteractableUserWidgetBase* NewWidget = OnWidgetCreated())
		{
			AddWidget(NewWidget);
		}
	}
}

void UInteractableUserWidgetGroup::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInteractableUserWidgetGroup::NativeDestruct()
{
	Super::NativeDestruct();
}

void UInteractableUserWidgetGroup::AddWidget(UInteractableUserWidgetBase* InWidget)
{
	if (!IsDesignTime())
	{
		DEnsureLOG(DLogUI, !IsValid(InWidget) || !IsValid(CommonButtonGroup))
		CommonButtonGroup->AddWidget(InWidget->ActiveCommonButton);
	}

	InteractableUserWidgets.Add(InWidget);
	if (Panel_Content)
	{
		int32 InIndex;
		InteractableUserWidgets.Find(InWidget, InIndex);

		UPanelSlot* NewSlot = Panel_Content->AddChild(InWidget);
		OnWidgetAdded(InWidget, NewSlot, InIndex);
	}
}

void UInteractableUserWidgetGroup::RemoveWidget(UInteractableUserWidgetBase* InWidget)
{
	if (!IsDesignTime())
	{
		DEnsureLOG(DLogUI, !IsValid(InWidget) || !IsValid(CommonButtonGroup))
		CommonButtonGroup->RemoveWidget(InWidget->ActiveCommonButton);
	}

	InteractableUserWidgets.Remove(InWidget);
	if (Panel_Content)
	{
		Panel_Content->RemoveChild(InWidget);
		OnWidgetRemoved(InWidget);
	}
}

UInteractableUserWidgetBase* UInteractableUserWidgetGroup::GetWidget(int32 Index)
{
	if (InteractableUserWidgets.IsValidIndex(Index))
	{
		return InteractableUserWidgets[Index];
	}

	return nullptr;
}

UInteractableUserWidgetBase* UInteractableUserWidgetGroup::OnWidgetCreated_Implementation()
{
	return nullptr;
}
