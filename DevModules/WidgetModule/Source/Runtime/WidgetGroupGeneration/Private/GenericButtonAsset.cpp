// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonAsset.h"

#include "GenericButtonBuilder.h"
#include "GenericButtonBuilderSetting.h"
#include "GenericButtonBuilderSettingAsset.h"
#include "WidgetType.h"
#include "MVVM/WidgetDescriptionViewModel.h"
#include "Type/DebugType.h"

UGenericButtonAsset::UGenericButtonAsset(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UGenericButtonAsset::IsContainButtonTag(FGameplayTag InButtonTag)
{
	if (!InButtonTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is InValid"))
		return false;
	}

	for (const auto& Builder : ButtonBuilders)
	{
		if (Builder->ButtonTag == InButtonTag)
		{
			return true;
		}
	}

	return false;
}

#if WITH_EDITOR

void UGenericButtonAsset::GenerateButtons()
{
	if (!ButtonBuilderSetting)
	{
		GenericNOTIFY(TEXT("Button Builder Setting is InValid"))
		return;
	}

	if (!ButtonBuilderSetting->RootButtonTag.IsValid())
	{
		GenericNOTIFY(TEXT("Root Button Tag is InValid"))
		return;
	}

	Modify();

	for (auto& BuilderSetting : ButtonBuilderSetting->GenericButtonBuilderSettings)
	{
		if (!BuilderSetting->BuilderClass)
		{
			continue;
		}

		if (IsContainButtonTag(BuilderSetting->ButtonTag))
		{
			continue;
		}

		UGenericButtonBuilder* NewBuilder = NewObject<UGenericButtonBuilder>(this, BuilderSetting->BuilderClass);
		NewBuilder->ButtonTag = BuilderSetting->ButtonTag;

		if (NewBuilder->WidgetDescriptionViewModel)
		{
			NewBuilder->WidgetDescriptionViewModel->PrimaryName = FText::FromString(BuilderSetting->DevComment);
		}

		ButtonBuilders.Add(NewBuilder);
	}

	GenericNOTIFY(TEXT("Generate Menu Finish"))
}

#endif

FGameplayTag UGenericButtonAsset::GetRootButtonTag() const
{
	if (ButtonBuilderSetting)
	{
		return ButtonBuilderSetting->RootButtonTag;
	}

	return FGameplayTag::EmptyTag;
}
