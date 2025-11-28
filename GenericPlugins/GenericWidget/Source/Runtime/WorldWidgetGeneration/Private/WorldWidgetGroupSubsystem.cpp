// Copyright ChenTaiye 2025. All Rights Reserved.

#include "WorldWidgetGroupSubsystem.h"

#include "GenericButtonWidget.h"
#include "GenericButtonGroup.h"
#include "WidgetType.h"
#include "WorldWidgetComponent.h"
#include "WorldWidgetSubsystem.h"

UWorldWidgetGroupSubsystem* UWorldWidgetGroupSubsystem::Get(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetSubsystem<ThisClass>();
	}
	return nullptr;
}

void UWorldWidgetGroupSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UWorldWidgetSubsystem::Delegate_OnWorldWidgetComponentActiveStateChanged.AddUObject(this, &UWorldWidgetGroupSubsystem::OnWorldWidgetComponentActiveStateChanged);
}

void UWorldWidgetGroupSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UWorldWidgetSubsystem::Delegate_OnWorldWidgetComponentActiveStateChanged.RemoveAll(this);
}

UGenericButtonGroup* UWorldWidgetGroupSubsystem::GetWorldWidgetGroup(FGameplayTag InGroupTag)
{
	if (WorldWidgetGroupMapping.Contains(InGroupTag))
	{
		return WorldWidgetGroupMapping.FindRef(InGroupTag);
	}
	return nullptr;
}

void UWorldWidgetGroupSubsystem::OnWorldWidgetComponentActiveStateChanged(UWorldWidgetComponent* InWorldWidgetComponent, bool IsActive)
{
	if (!IsValid(InWorldWidgetComponent))
	{
		GenericLOG(GenericLogUI, Error, TEXT("InWorldWidgetComponent Is InValid"))
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
