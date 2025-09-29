// Copyright ChenTaiye 2025. All Rights Reserved.


#include "UMG/Spawner/PropertyValueSpawner.h"

#include "PropertyType.h"
#include "Type/DebugType.h"
#include "UMG/PropertyValue/PropertyValueBase.h"
#include "UMG/PropertyValue/PropertyValueWarning.h"

#define LOCTEXT_NAMESPACE "FGenericProperty"

TSharedRef<SWidget> UPropertyValueSpawner::RebuildWidget()
{
	MyBox = SNew(SBox);

	if (IsDesignTime())
	{
		MyBox->SetContent(
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromName(GetFName()))
			]
		);
	}

	return MyBox.ToSharedRef();
}

void UPropertyValueSpawner::SynchronizeProperties()
{
	Super::SynchronizeProperties();

#if WITH_EDITOR
	ClearChildren();

	if (PropertyValueWidgetClass)
	{
		PropertyValueWidget = CreateWidget<UPropertyValueBase>(this, PropertyValueWidgetClass);
		AddChild(PropertyValueWidget);
	}
	else
	{
		if (PropertyWarningClass)
		{
			UPropertyValueWarning* WarningWidget = CreateWidget<UPropertyValueWarning>(this, PropertyWarningClass);
			AddChild(WarningWidget);
		}
	}
#endif
}

void UPropertyValueSpawner::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	PropertyValueWidget = nullptr;
}

bool UPropertyValueSpawner::SpawnPropertyWidget(const TSubclassOf<UPropertyValueBase>& InClass, UPropertyViewModel* InViewModel)
{
	if (!InClass)
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyValueWidgetClass Is InValid"))

		FFormatNamedArguments Arguments;
		SpawnPropertyValueWarningWidget(FText::FromString(TEXT("Property Value Widget Class Is InValid")));

		return false;
	}

	if (!IsValid(InViewModel))
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyViewModel Is InValid"))

		FFormatNamedArguments Arguments;
		SpawnPropertyValueWarningWidget(FText::FromString(TEXT("Property View Model Is InValid")));

		return false;
	}

	ClearChildren();

	PropertyValueWidget = CreateWidget<UPropertyValueBase>(this, InClass);

	if (!PropertyValueWidget->GetSupportPropertyViewModelClass() || !InViewModel->GetClass()->IsChildOf(PropertyValueWidget->GetSupportPropertyViewModelClass()))
	{
		PropertyValueWidget->MarkAsGarbage();

		FFormatNamedArguments Arguments;
		Arguments.Add(TEXT("PropertyWidgetClass"), FText::FromString(*InClass->GetName()));
		Arguments.Add(TEXT("PropertyViewModelClass"), FText::FromString(*InViewModel->GetClass()->GetName()));
		SpawnPropertyValueWarningWidget(FText::Format(LOCTEXT("SpawnPropertyWidgetError", "Property Widget Class : {PropertyWidgetClass} Not Support Property View Model : {PropertyViewModelClass}"), Arguments));

		return false;
	}

	PropertyValueWidget->SetPropertyViewModel(InViewModel);
	AddChild(PropertyValueWidget);

	return true;
}

UPropertyValueBase* UPropertyValueSpawner::GetPropertyWidget()
{
	return PropertyValueWidget;
}

void UPropertyValueSpawner::SpawnPropertyValueWarningWidget(const FText& InWarningText)
{
	if (PropertyWarningClass)
	{
		UPropertyValueWarning* WarningWidget = CreateWidget<UPropertyValueWarning>(this, PropertyWarningClass);
		WarningWidget->SetWarningText(InWarningText);
		AddChild(WarningWidget);
	}
}

#undef LOCTEXT_NAMESPACE
