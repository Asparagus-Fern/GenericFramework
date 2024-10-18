// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PropertyPanel.h"

#include "PropertyRegistry.h"
#include "Collection/PropertyCollection.h"
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

	if (!PropertyRegistry)
	{
		CompileLog.Error(FText::Format(LOCTEXT("Error_PropertyPanel_MissingPropertyRegistry", "{0} has no PropertyRegistry specified."), FText::FromString(GetName())));
	}
}

#endif

void UPropertyPanel::SetupProperty()
{
	DEnsureLOG(LogProperty, PropertyRegistry)

	Registry = NewObject<UPropertyRegistry>(this, PropertyRegistry);
	Registry->Initialize(); 
}

void UPropertyPanel::ClearupProperty()
{
	SetPropertyCollection(nullptr);
}

void UPropertyPanel::RefreshProperty()
{
	SetPropertyCollection(Collection);
}

void UPropertyPanel::SetPropertyCollection(UPropertyCollection* InCollection)
{
	if (Collection)
	{
		/* 如果和当前不一样，标记垃圾回收 */
		if (Collection != InCollection)
		{
			Collection->MarkAsGarbage();
		}
		/* 如果和当前一样，刷新面板 */
		else
		{
			Refresh();
			return;
		}
	}

	if (InCollection)
		Collection = InCollection;
	else
		Collection = nullptr;

	/* 刷新当前UI */
	Refresh();
}

void UPropertyPanel::Refresh()
{
	RefreshPropertyWidget(Collection);
}

void UPropertyPanel::RefreshPropertyWidget(UPropertyCollection* InCollection) const
{
	/* 属性属性细节面板 */
	Panel_ProertyDetail->UpdatePropertyDetail(InCollection);

	if (Panel_ProertyDetailDescription)
	{
		Panel_ProertyDetailDescription->UpdatePropertyDetailDescription(InCollection);
	}
}

#undef LOCTEXT_NAMESPACE
