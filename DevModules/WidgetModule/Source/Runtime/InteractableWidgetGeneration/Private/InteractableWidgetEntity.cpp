// Copyright ChenTaiye 2025. All Rights Reserved.


#include "InteractableWidgetEntity.h"

#include "InteractableWidgetBase.h"

void UInteractableWidgetEntity::NativeOnCreate()
{
	Super::NativeOnCreate();
}

void UInteractableWidgetEntity::NativeOnDestroy()
{
	Super::NativeOnDestroy();
}

void UInteractableWidgetEntity::OnEntityWidgetInitialized()
{
	Super::OnEntityWidgetInitialized();
	BindWidgetEvent();
}

void UInteractableWidgetEntity::OnEntityWidgetDeinitialized()
{
	Super::OnEntityWidgetDeinitialized();
	UnBindWidgetEvent();
}

void UInteractableWidgetEntity::BindWidgetEvent()
{
	if (UInteractableWidgetBase* InteractableWidget = Cast<UInteractableWidgetBase>(GetWidget()))
	{
		InteractableWidget->OnButtonPressed.AddUniqueDynamic(this, &UInteractableWidgetEntity::HandleOnEntityPressed);
		InteractableWidget->OnButtonReleased.AddUniqueDynamic(this, &UInteractableWidgetEntity::HandleOnEntityReleased);
		InteractableWidget->OnButtonHovered.AddUniqueDynamic(this, &UInteractableWidgetEntity::HandleOnEntityHovered);
		InteractableWidget->OnButtonUnhovered.AddUniqueDynamic(this, &UInteractableWidgetEntity::HandleOnEntityUnhovered);
		InteractableWidget->OnButtonClicked.AddUniqueDynamic(this, &UInteractableWidgetEntity::HandleOnEntityClicked);
		InteractableWidget->OnButtonDoubleClicked.AddUniqueDynamic(this, &UInteractableWidgetEntity::HandleOnEntityDoubleClicked);
		InteractableWidget->OnButtonSelectionChanged.AddUniqueDynamic(this, &UInteractableWidgetEntity::HandleOnEntitySelectionChanged);
	}
}

void UInteractableWidgetEntity::UnBindWidgetEvent()
{
	if (UInteractableWidgetBase* InteractableWidget = Cast<UInteractableWidgetBase>(GetWidget()))
	{
		InteractableWidget->OnButtonPressed.RemoveAll(this);
		InteractableWidget->OnButtonReleased.RemoveAll(this);
		InteractableWidget->OnButtonHovered.RemoveAll(this);
		InteractableWidget->OnButtonUnhovered.RemoveAll(this);
		InteractableWidget->OnButtonClicked.RemoveAll(this);
		InteractableWidget->OnButtonDoubleClicked.RemoveAll(this);
		InteractableWidget->OnButtonSelectionChanged.RemoveAll(this);
	}
}

void UInteractableWidgetEntity::Pressed()
{
	GetOnEntityPressed().Broadcast(this);
}

void UInteractableWidgetEntity::Released()
{
	GetOnEntityReleased().Broadcast(this);
}

void UInteractableWidgetEntity::Hovered()
{
	GetOnEntityHovered().Broadcast(this);
}

void UInteractableWidgetEntity::Unhovered()
{
	GetOnEntityUnhovered().Broadcast(this);
}

void UInteractableWidgetEntity::Clicked()
{
	GetOnEntityClicked().Broadcast(this);
}

void UInteractableWidgetEntity::DoubleClicked()
{
	GetOnEntityDoubleClicked().Broadcast(this);
}

void UInteractableWidgetEntity::ChangeSelection(bool Selection)
{
	GetOnEntitySelectionChanged().Broadcast(this, Selection);
}

void UInteractableWidgetEntity::InternalPressed()
{
	OnEntityPressed();
}

void UInteractableWidgetEntity::InternalReleased()
{
	OnEntityReleased();
}

void UInteractableWidgetEntity::InternalHovered()
{
	OnEntityHovered();
}

void UInteractableWidgetEntity::InternalUnhovered()
{
	OnEntityUnhovered();
}

void UInteractableWidgetEntity::InternalClicked()
{
	OnEntityClicked();
}

void UInteractableWidgetEntity::InternalDoubleClicked()
{
	OnEntityDoubleClicked();
}

void UInteractableWidgetEntity::InternalChangeSelection(bool Selection)
{
	OnEntitySelectionChanged(Selection);
}

void UInteractableWidgetEntity::HandleOnEntityPressed(UInteractableWidgetBase* Button)
{
	Pressed();
}

void UInteractableWidgetEntity::HandleOnEntityReleased(UInteractableWidgetBase* Button)
{
	Released();
}

void UInteractableWidgetEntity::HandleOnEntityHovered(UInteractableWidgetBase* Button)
{
	Hovered();
}

void UInteractableWidgetEntity::HandleOnEntityUnhovered(UInteractableWidgetBase* Button)
{
	Unhovered();
}

void UInteractableWidgetEntity::HandleOnEntityClicked(UInteractableWidgetBase* Button)
{
	Clicked();
}

void UInteractableWidgetEntity::HandleOnEntityDoubleClicked(UInteractableWidgetBase* Button)
{
	DoubleClicked();
}

void UInteractableWidgetEntity::HandleOnEntitySelectionChanged(UInteractableWidgetBase* Button, bool Selection)
{
	ChangeSelection(Selection);
}

void UInteractableWidgetEntity::OnEntityPressed_Implementation()
{
}

void UInteractableWidgetEntity::OnEntityReleased_Implementation()
{
}

void UInteractableWidgetEntity::OnEntityHovered_Implementation()
{
}

void UInteractableWidgetEntity::OnEntityUnhovered_Implementation()
{
}

void UInteractableWidgetEntity::OnEntityClicked_Implementation()
{
}

void UInteractableWidgetEntity::OnEntityDoubleClicked_Implementation()
{
}

void UInteractableWidgetEntity::OnEntitySelectionChanged_Implementation(bool Selection)
{
}
