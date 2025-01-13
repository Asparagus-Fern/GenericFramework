// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableWidgetGroup.h"

#include "Group/CommonButton.h"
#include "Group/CommonButtonGroup.h"

void UInteractableWidgetGroup::NativePreConstruct()
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
		if (UInteractableWidgetBase* NewWidget = OnWidgetCreated())
		{
			AddWidget(NewWidget);
		}
	}
}

void UInteractableWidgetGroup::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInteractableWidgetGroup::NativeDestruct()
{
	Super::NativeDestruct();
}

void UInteractableWidgetGroup::AddWidget(UInteractableWidgetBase* InWidget)
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

void UInteractableWidgetGroup::RemoveWidget(UInteractableWidgetBase* InWidget)
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

UInteractableWidgetBase* UInteractableWidgetGroup::GetWidget(int32 Index)
{
	if (InteractableUserWidgets.IsValidIndex(Index))
	{
		return InteractableUserWidgets[Index];
	}

	return nullptr;
}

UInteractableWidgetBase* UInteractableWidgetGroup::OnWidgetCreated_Implementation()
{
	return nullptr;
}
