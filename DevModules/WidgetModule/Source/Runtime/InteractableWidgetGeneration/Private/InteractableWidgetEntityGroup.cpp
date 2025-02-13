// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableWidgetEntityGroup.h"

#include "InteractableWidgetBase.h"
#include "InteractableWidgetEntity.h"

void UInteractableWidgetEntityGroup::OnCreate_Implementation()
{
	IStateInterface::OnCreate_Implementation();
}

void UInteractableWidgetEntityGroup::OnDestroy_Implementation()
{
	IStateInterface::OnDestroy_Implementation();
	ClearupEntity();
}

void UInteractableWidgetEntityGroup::AddEntities(TArray<UInteractableWidgetEntity*> InEntities)
{
	for (const auto& InEntity : InEntities)
	{
		AddEntity(InEntity);
	}
}

void UInteractableWidgetEntityGroup::AddEntity(UInteractableWidgetEntity* InEntity)
{
	if (!IsValid(InEntity))
	{
		DLOG(DLogUI, Error, TEXT("InEntity Is InValid"))
		return;
	}

	if (HasEntity(InEntity))
	{
		DLOG(DLogUI, Warning, TEXT("InEntity Is Already In The Group"))
		return;
	}

	Entities.Add(InEntity);

	InEntity->GetOnEntityPressed().AddUObject(this, &UInteractableWidgetEntityGroup::HandleOnEntityPressed);
	InEntity->GetOnEntityReleased().AddUObject(this, &UInteractableWidgetEntityGroup::HandleOnEntityReleased);
	InEntity->GetOnEntityHovered().AddUObject(this, &UInteractableWidgetEntityGroup::HandleOnEntityHovered);
	InEntity->GetOnEntityUnhovered().AddUObject(this, &UInteractableWidgetEntityGroup::HandleOnEntityUnhovered);
	InEntity->GetOnEntityClicked().AddUObject(this, &UInteractableWidgetEntityGroup::HandleOnEntityClicked);
	InEntity->GetOnEntityDoubleClicked().AddUObject(this, &UInteractableWidgetEntityGroup::HandleOnEntityDoubleClicked);
	InEntity->GetOnEntitySelectionChanged().AddUObject(this, &UInteractableWidgetEntityGroup::HandleOnEntitySelectionChanged);

	if (!HasSelectedEntity() && InEntity->bDefaultSelected)
	{
		SetSelectedEntity(InEntity);
	}
}

void UInteractableWidgetEntityGroup::AddWidgets(TArray<UInteractableWidgetBase*> InWidgets)
{
	for (const auto& InWidget : InWidgets)
	{
		AddWidget(InWidget);
	}
}

void UInteractableWidgetEntityGroup::AddWidget(UInteractableWidgetBase* InWidget)
{
	if (!IsValid(InWidget))
	{
		DLOG(DLogUI, Error, TEXT("InWidget Is InValid"))
		return;
	}

	UInteractableWidgetEntity* NewEntity = NewObject<UInteractableWidgetEntity>(InWidget);
	NewEntity->SetWidget(InWidget);
	NewEntity->BindWidgetEvent();
	InWidget->SetWidgetEntity(NewEntity);

	AddEntity(NewEntity);
}

void UInteractableWidgetEntityGroup::RemoveEntities(TArray<UInteractableWidgetEntity*> InEntities)
{
	for (const auto& InEntity : InEntities)
	{
		RemoveEntity(InEntity);
	}
}

void UInteractableWidgetEntityGroup::RemoveEntity(UInteractableWidgetEntity* InEntity)
{
	if (!IsValid(InEntity))
	{
		DLOG(DLogUI, Error, TEXT("InEntity Is InValid"))
		return;
	}

	if (!HasEntity(InEntity))
	{
		DLOG(DLogUI, Warning, TEXT("InEntity Is Not In The Group"))
		return;
	}

	if (SelectedEntity == InEntity)
	{
		DeselectAll();
	}

	InEntity->GetOnEntityPressed().RemoveAll(this);
	InEntity->GetOnEntityReleased().RemoveAll(this);
	InEntity->GetOnEntityHovered().RemoveAll(this);
	InEntity->GetOnEntityUnhovered().RemoveAll(this);
	InEntity->GetOnEntityClicked().RemoveAll(this);
	InEntity->GetOnEntityDoubleClicked().RemoveAll(this);
	InEntity->GetOnEntitySelectionChanged().RemoveAll(this);

	Entities.Remove(InEntity);
}

void UInteractableWidgetEntityGroup::RemoveEntityByIndex(int32 Index)
{
	if (UInteractableWidgetEntity* Entity = GetEntityByIndex(Index))
	{
		RemoveEntity(Entity);
	}
	else
	{
		DLOG(DLogUI, Warning, TEXT("Index Is InValid"))
	}
}

void UInteractableWidgetEntityGroup::RemoveWidgets(TArray<UInteractableWidgetBase*> InWidgets)
{
	for (const auto& InWidget : InWidgets)
	{
		RemoveWidget(InWidget);
	}
}

void UInteractableWidgetEntityGroup::RemoveWidget(UInteractableWidgetBase* InWidget)
{
	if (!IsValid(InWidget))
	{
		DLOG(DLogUI, Error, TEXT("InWidget Is InValid"))
		return;
	}

	UInteractableWidgetEntity* Entity = InWidget->GetWidgetEntity<UInteractableWidgetEntity>();
	InWidget->SetWidgetEntity(nullptr);

	RemoveEntity(Entity);
	Entity->MarkAsGarbage();
}

void UInteractableWidgetEntityGroup::ClearupEntity()
{
	if (IsValid(SelectedEntity))
	{
		DeselectAll();
	}

	Entities.Reset();
	SelectedEntity = nullptr;
	LastSelectedEntity = nullptr;
}

bool UInteractableWidgetEntityGroup::HasLastSelectedEntity() const
{
	return IsValid(LastSelectedEntity);
}

bool UInteractableWidgetEntityGroup::HasSelectedEntity() const
{
	return IsValid(SelectedEntity);
}

void UInteractableWidgetEntityGroup::SetSelectedEntity(UInteractableWidgetEntity* InEntity)
{
	if (!IsValid(InEntity))
	{
		DLOG(DLogUI, Error, TEXT("InEntity Is InValid"))
		return;
	}

	if (!InEntity->bIsEnable)
	{
		DLOG(DLogUI, Warning, TEXT("InEntity Is Disable To Interact"))
		return;
	}

	if (!InEntity->bSelectable)
	{
		DLOG(DLogUI, Warning, TEXT("InEntity Is Disable To Selected"))
		return;
	}

	HandleOnEntitySelectionChanged(InEntity, true);
}

void UInteractableWidgetEntityGroup::SetSelectedEntityByIndex(int32 Index)
{
	if (UInteractableWidgetEntity* Entity = GetEntityByIndex(Index))
	{
		SetSelectedEntity(Entity);
	}
	else
	{
		DLOG(DLogUI, Warning, TEXT("Index Is InValid"))
	}
}

UInteractableWidgetEntity* UInteractableWidgetEntityGroup::GetLastSelectedEntity() const
{
	return LastSelectedEntity;
}

int32 UInteractableWidgetEntityGroup::GetLastSelectedEntityIndex() const
{
	if (UInteractableWidgetEntity* Last = GetLastSelectedEntity())
	{
		return FindEntityIndex(Last);
	}
	return -1;
}

UInteractableWidgetEntity* UInteractableWidgetEntityGroup::GetSelectedEntity() const
{
	return SelectedEntity;
}

int32 UInteractableWidgetEntityGroup::GetSelectedEntityIndex() const
{
	if (UInteractableWidgetEntity* Selected = GetSelectedEntity())
	{
		return FindEntityIndex(Selected);
	}
	return -1;
}

void UInteractableWidgetEntityGroup::SelectPreviousEntity(bool bAllowWrapping)
{
	if (!HasSelectedEntity())
	{
		return;
	}

	const int32 PreviousIndex = GetSelectedEntityIndex() - 1;
	if (PreviousIndex >= 0)
	{
		SetSelectedEntityByIndex(PreviousIndex);
	}
	else if (bAllowWrapping)
	{
		SetSelectedEntityByIndex(GetEntityCount() - 1);
	}
}

void UInteractableWidgetEntityGroup::SelectLastEntity()
{
	if (HasLastSelectedEntity())
	{
		SetSelectedEntity(LastSelectedEntity);
	}
}

void UInteractableWidgetEntityGroup::SelectNextEntity(bool bAllowWrapping)
{
	if (!HasSelectedEntity())
	{
		return;
	}

	const int32 NextIndex = GetSelectedEntityIndex() + 1;
	if (NextIndex < GetEntityCount())
	{
		SetSelectedEntityByIndex(NextIndex);
	}
	else if (bAllowWrapping)
	{
		SetSelectedEntityByIndex(0);
	}
}

void UInteractableWidgetEntityGroup::DeselectAll()
{
	if (HasSelectedEntity())
	{
		SelectedEntity->InternalChangeSelection(false);
		LastSelectedEntity = SelectedEntity;
		SelectedEntity = nullptr;
	}
}

bool UInteractableWidgetEntityGroup::HasEntity(UInteractableWidgetEntity* InEntity) const
{
	return Entities.Contains(InEntity);
}

int32 UInteractableWidgetEntityGroup::GetEntityCount() const
{
	return Entities.Num();
}

UInteractableWidgetEntity* UInteractableWidgetEntityGroup::GetEntityByIndex(int32 Index)
{
	if (Entities.IsValidIndex(Index))
	{
		return Entities[Index];
	}
	return nullptr;
}

int32 UInteractableWidgetEntityGroup::FindEntityIndex(UInteractableWidgetEntity* InEntity) const
{
	int32 Index;
	Entities.Find(InEntity, Index);
	return Index;
}

TArray<UInteractableWidgetEntity*> UInteractableWidgetEntityGroup::GetEntities() const
{
	return Entities;
}

void UInteractableWidgetEntityGroup::HandleOnEntityPressed(UInteractableWidgetEntity* InEntity)
{
	InEntity->InternalPressed();
	OnEntityPressed.Broadcast(InEntity);
}

void UInteractableWidgetEntityGroup::HandleOnEntityReleased(UInteractableWidgetEntity* InEntity)
{
	InEntity->InternalReleased();
	OnEntityReleased.Broadcast(InEntity);
}

void UInteractableWidgetEntityGroup::HandleOnEntityHovered(UInteractableWidgetEntity* InEntity)
{
	InEntity->InternalHovered();
	OnEntityHovered.Broadcast(InEntity);
}

void UInteractableWidgetEntityGroup::HandleOnEntityUnhovered(UInteractableWidgetEntity* InEntity)
{
	InEntity->InternalUnhovered();
	OnEntityUnhovered.Broadcast(InEntity);
}

void UInteractableWidgetEntityGroup::HandleOnEntityClicked(UInteractableWidgetEntity* InEntity)
{
	InEntity->InternalClicked();
	OnEntityClicked.Broadcast(InEntity);
	HandleOnEntitySelectionChanged(InEntity, true);
}

void UInteractableWidgetEntityGroup::HandleOnEntityDoubleClicked(UInteractableWidgetEntity* InEntity)
{
	InEntity->InternalDoubleClicked();
	OnEntityDoubleClicked.Broadcast(InEntity);
}

void UInteractableWidgetEntityGroup::HandleOnEntitySelectionChanged(UInteractableWidgetEntity* InEntity, bool Selection)
{
	if (!HasSelectedEntity())
	{
		SelectedEntity = InEntity;
		InEntity->InternalChangeSelection(true);
		OnEntitySelectionChanged.Broadcast(InEntity, true);
		return;
	}

	if (SelectedEntity == InEntity)
	{
		if (InEntity->bToggleable)
		{
			InEntity->InternalChangeSelection(false);

			LastSelectedEntity = SelectedEntity;
			SelectedEntity = nullptr;

			OnEntitySelectionChanged.Broadcast(InEntity, false);
		}
	}
	else
	{
		SelectedEntity->InternalChangeSelection(false);
		OnEntitySelectionChanged.Broadcast(SelectedEntity, false);

		LastSelectedEntity = SelectedEntity;
		SelectedEntity = InEntity;

		InEntity->InternalChangeSelection(true);
		OnEntitySelectionChanged.Broadcast(InEntity, true);
	}
}
