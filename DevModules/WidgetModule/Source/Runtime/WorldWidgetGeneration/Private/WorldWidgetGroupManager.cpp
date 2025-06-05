// Copyright ChenTaiye 2025. All Rights Reserved.


#include "WorldWidgetGroupManager.h"

#include "InteractableWidgetBase.h"
#include "InteractableWidgetEntityGroup.h"
#include "WorldWidgetComponent.h"
#include "WorldWidgetManager.h"

bool UWorldWidgetGroupManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UWorldWidgetGroupManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	UWorldWidgetManager::Delegate_OnWorldWidgetComponentActiveStateChanged.AddUObject(this, &UWorldWidgetGroupManager::OnWorldWidgetComponentActiveStateChanged);
}

void UWorldWidgetGroupManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	UWorldWidgetManager::Delegate_OnWorldWidgetComponentActiveStateChanged.RemoveAll(this);
}

bool UWorldWidgetGroupManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

UInteractableWidgetEntityGroup* UWorldWidgetGroupManager::GetWorldWidgetGroup(FGameplayTag InGroupTag)
{
	if (WorldWidgetGroupMapping.Contains(InGroupTag))
	{
		return WorldWidgetGroupMapping.FindRef(InGroupTag);
	}
	return nullptr;
}

void UWorldWidgetGroupManager::OnWorldWidgetComponentActiveStateChanged(UWorldWidgetComponent* InWorldWidgetComponent, bool IsActive)
{
	if (!IsValid(InWorldWidgetComponent))
	{
		GenericLOG(UILog, Error, TEXT("InWorldWidgetComponent Is NULL"))
		return;
	}

	if (!InWorldWidgetComponent->GroupTag.IsValid())
	{
		/* Only Make Group While WorldWidgetTag Is Valid */
		return;
	}

	if (!InWorldWidgetComponent->WorldWidget)
	{
		/* Only Make Group While WorldWidget Is Valid */
		return;
	}

	UInteractableWidgetBase* InteractableWidget = Cast<UInteractableWidgetBase>(InWorldWidgetComponent->WorldWidget);
	if (!IsValid(InteractableWidget))
	{
		/* Only Make Group While WorldWidget Is Base Of UInteractableWidgetBase */
		return;
	}

	if (IsActive)
	{
		/* Find Is ParentTag Registered */
		if (!WorldWidgetGroupMapping.Contains(InWorldWidgetComponent->GroupTag))
		{
			UInteractableWidgetEntityGroup* NewGroup = NewObject<UInteractableWidgetEntityGroup>(this);
			WorldWidgetGroupMapping.FindOrAdd(InWorldWidgetComponent->GroupTag, NewGroup);
		}

		UInteractableWidgetEntityGroup* Group = WorldWidgetGroupMapping.FindRef(InWorldWidgetComponent->GroupTag);
		Group->AddWidget(InteractableWidget);
	}
	else
	{
		UInteractableWidgetEntityGroup* Group = WorldWidgetGroupMapping.FindRef(InWorldWidgetComponent->GroupTag);
		Group->RemoveWidget(InteractableWidget);

		if (Group->GetEntityCount() == 0)
		{
			WorldWidgetGroupMapping.Remove(InWorldWidgetComponent->GroupTag);
			Group->MarkAsGarbage();
		}
	}
}
