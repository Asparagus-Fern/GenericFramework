// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableWidgetEntity.h"

#include "InteractableWidgetBase.h"

void UInteractableWidgetEntity::OpenEntityWidget_Implementation()
{
	Super::OpenEntityWidget_Implementation();

	if (UInteractableWidgetBase* Widget = Cast<UInteractableWidgetBase>(GetWidget()))
	{
		Widget->OnButtonPressed.AddUniqueDynamic(this, &UInteractableWidgetEntity::HandleOnEntityPressed);
		Widget->OnButtonReleased.AddUniqueDynamic(this, &UInteractableWidgetEntity::HandleOnEntityReleased);
		Widget->OnButtonHovered.AddUniqueDynamic(this, &UInteractableWidgetEntity::HandleOnEntityHovered);
		Widget->OnButtonUnhovered.AddUniqueDynamic(this, &UInteractableWidgetEntity::HandleOnEntityUnhovered);
		Widget->OnButtonClicked.AddUniqueDynamic(this, &UInteractableWidgetEntity::HandleOnEntityClicked);
		Widget->OnButtonDoubleClicked.AddUniqueDynamic(this, &UInteractableWidgetEntity::HandleOnEntityDoubleClicked);
		Widget->OnButtonSelectionChanged.AddUniqueDynamic(this, &UInteractableWidgetEntity::HandleOnEntitySelectionChanged);
	}
}

void UInteractableWidgetEntity::CloseEntityWidget_Implementation()
{
	Super::CloseEntityWidget_Implementation();

	if (UInteractableWidgetBase* Widget = Cast<UInteractableWidgetBase>(GetWidget()))
	{
		Widget->OnButtonPressed.RemoveAll(this);
		Widget->OnButtonReleased.RemoveAll(this);
		Widget->OnButtonHovered.RemoveAll(this);
		Widget->OnButtonUnhovered.RemoveAll(this);
		Widget->OnButtonClicked.RemoveAll(this);
		Widget->OnButtonDoubleClicked.RemoveAll(this);
		Widget->OnButtonSelectionChanged.RemoveAll(this);
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
