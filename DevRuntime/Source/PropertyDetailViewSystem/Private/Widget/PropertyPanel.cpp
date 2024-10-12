// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PropertyPanel.h"

#include "Collection/PropertyCollection.h"
#include "DataSource/PropertySourceHandle.h"
#include "Widget/PropertyDetailDescriptionPanel.h"
#include "Widget/PropertyDetailPanel.h"

#if WITH_EDITOR
#include "Editor/WidgetCompilerLog.h"
#endif

#define LOCTEXT_NAMESPACE "PropertyDetailViewSystem"

void UPropertyPanel::NativeConstruct()
{
	Super::NativeConstruct();
	SetupProperty();
}

void UPropertyPanel::NativeDestruct()
{
	Super::NativeDestruct();
}

#if WITH_EDITOR

void UPropertyPanel::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!PropertySource)
	{
		CompileLog.Error(FText::Format(LOCTEXT("Error_PropertyPanel_MissingPropertySource", "{0} has no PropertySource specified."), FText::FromString(GetName())));
	}
}

#endif

void UPropertyPanel::SetupProperty()
{
	if (!PropertySource)
	{
		LOG(LogProperty, Error, TEXT("MissingPropertySource"))
		return;
	}

	UPropertySourceHandle* NewPropertySourceHandle = NewObject<UPropertySourceHandle>(this, PropertySource);
	NewPropertySourceHandle->Initialize();
	PropertyCollection = NewPropertySourceHandle->GetPropertyCollection();

	RefreshPropertyWidget();
}

void UPropertyPanel::ClearupProperty()
{
	PropertyCollection->MarkAsGarbage();
	PropertyCollection = nullptr;
	RefreshPropertyWidget();
}

void UPropertyPanel::RefreshProperty()
{
	ClearupProperty();
	SetupProperty();
}

void UPropertyPanel::RefreshPropertyWidget()
{
	Panel_ProertyDetail->UpdatePropertyDetail(PropertyCollection);

	if (Panel_ProertyDetailDescription)
	{
		Panel_ProertyDetailDescription->UpdatePropertyDetailDescription(PropertyCollection);
	}
}

#undef LOCTEXT_NAMESPACE
