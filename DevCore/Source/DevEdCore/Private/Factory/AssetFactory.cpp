// Fill out your copyright notice in the Description page of Project Settings.


#include "Factory/AssetFactory.h"

#include "Kismet2/SClassPickerDialog.h"

UAssetFactory::UAssetFactory()
{
	bCreateNew = true;
	SupportedClass = UObject::StaticClass();

	AssetName = FText::FromString("NewAsset");
	bPickClass = false;
	PickClass = nullptr;
}

FText UAssetFactory::GetDisplayName() const
{
	return AssetName;
}

bool UAssetFactory::ConfigureProperties()
{
	if (bPickClass)
	{
		FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");

		TSharedRef<FAssetFilter> Filter = MakeShareable(new FAssetFilter());
		ConfigureFilter(Filter);

		FClassViewerInitializationOptions Options;
		ConfigureClassViewerOptions(Options);
		Options.ClassFilters.Add(Filter);

		const FText TitleText = FText::FromString("Pick Parent Class");
		bool IsSuccessful = SClassPickerDialog::PickClass(TitleText, Options, PickClass, SupportedClass);

		if (!IsSuccessful || !PickClass)
		{
			return false;
		}
	}

	return true;
}

void UAssetFactory::ConfigureClassViewerOptions(FClassViewerInitializationOptions& Options)
{
	Options.DisplayMode = EClassViewerDisplayMode::Type::TreeView;
	Options.Mode = EClassViewerMode::ClassPicker;
	Options.bShowNoneOption = false;
	Options.bExpandAllNodes = true;
	Options.bShowDefaultClasses = true;
	Options.bShowClassesViewer = true;
}

void UAssetFactory::ConfigureFilter(TSharedRef<FAssetFilter>& Filter)
{
	Filter->DisallowedClassFlags = CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_Hidden | CLASS_HideDropDown;
}
