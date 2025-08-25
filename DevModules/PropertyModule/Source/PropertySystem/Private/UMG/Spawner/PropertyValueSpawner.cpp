// Copyright ChenTaiye 2025. All Rights Reserved.


#include "UMG/Spawner/PropertyValueSpawner.h"

#include "PropertyType.h"
#include "Type/DebugType.h"
#include "UMG/PropertyValue/PropertyValueBase.h"

TSharedRef<SWidget> UPropertyValueSpawner::RebuildWidget()
{
	return Super::RebuildWidget();
}

void UPropertyValueSpawner::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	ClearChildren();
	if (IsDesignTime() && PropertyWidgetClass)
	{
		PropertyWidget = CreateWidget<UPropertyValueBase>(this, PropertyWidgetClass);
		AddChild(PropertyWidget);
	}
}

void UPropertyValueSpawner::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	PropertyWidget = nullptr;
}

void UPropertyValueSpawner::SpawnPropertyWidget(const TSubclassOf<UPropertyValueBase>& InClass, UPropertyValueViewModel* InViewModel)
{
	ensureAlways(InClass);

	ClearChildren();

	PropertyWidget = CreateWidget<UPropertyValueBase>(this, InClass);

	if (InViewModel->GetClass()->IsChildOf(PropertyWidget->GetSupportViewModelClass()))
	{
		PropertyWidget->SetViewModel(InViewModel);
		AddChild(PropertyWidget);
	}
	else
	{
		PropertyWidget->MarkAsGarbage();
		GenericLOG(GenericLogProperty, Error, TEXT("Class : %s Not Support ViewModel : %s"), *InClass->GetName(), * InViewModel->GetClass()->GetName())
	}
}
