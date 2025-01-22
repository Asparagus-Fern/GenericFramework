// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableWidgetEntity.h"

void UInteractableWidgetEntity::OnSelected_Implementation()
{
}

void UInteractableWidgetEntity::OnDeSelected_Implementation()
{
}

void UInteractableWidgetEntity::NativeOnSelected()
{
	OnEntitySelectionChanged.Broadcast(this, true);
	OnSelected();
}

void UInteractableWidgetEntity::NativeOnDeSelected()
{
	OnEntitySelectionChanged.Broadcast(this, false);
	OnDeSelected();
}
