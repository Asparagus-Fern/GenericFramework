// Copyright ChenTaiye 2025. All Rights Reserved.


#include "WorldWidgetGroupManager.h"

#include "GenericButtonWidget.h"
#include "GenericButtonGroup.h"
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

UGenericButtonGroup* UWorldWidgetGroupManager::GetWorldWidgetGroup(FGameplayTag InGroupTag)
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
		GenericLOG(GenericLogUI, Error, TEXT("InWorldWidgetComponent Is NULL"))
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

	UGenericButtonWidget* InteractableWidget = Cast<UGenericButtonWidget>(InWorldWidgetComponent->WorldWidget);
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
			UGenericButtonGroup* NewGroup = NewObject<UGenericButtonGroup>(this);
			WorldWidgetGroupMapping.FindOrAdd(InWorldWidgetComponent->GroupTag, NewGroup);
		}

		UGenericButtonGroup* Group = WorldWidgetGroupMapping.FindRef(InWorldWidgetComponent->GroupTag);
		Group->AddButton(InteractableWidget);
	}
	else
	{
		UGenericButtonGroup* Group = WorldWidgetGroupMapping.FindRef(InWorldWidgetComponent->GroupTag);
		Group->RemoveButton(InteractableWidget);

		if (Group->GetButtonCount() == 0)
		{
			WorldWidgetGroupMapping.Remove(InWorldWidgetComponent->GroupTag);
			Group->MarkAsGarbage();
		}
	}
}
