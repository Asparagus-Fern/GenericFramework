// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Tools/FastSwitchLanguage.h"

#include "DevCoreStyle.h"
#include "DevFrameworkEdSubsystem.h"
#include "Internationalization/Culture.h"
#include "Kismet2/BlueprintEditorUtils.h"

#define LOCTEXT_NAMESPACE "FApplicationEditorModule"

void UFastSwitchLanguage::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	FDevFrameworkDelegate::OnToolBarSectionExtend.AddUObject(this, &UFastSwitchLanguage::OnToolBarSectionExtend);
}

void UFastSwitchLanguage::Deinitialize()
{
	Super::Deinitialize();
	FDevFrameworkDelegate::OnToolBarSectionExtend.RemoveAll(this);
}

void UFastSwitchLanguage::OnToolBarSectionExtend(FToolMenuSection& InToolMenuSection)
{
	InToolMenuSection.AddEntry
	(
		FToolMenuEntry::InitToolBarButton
		(
			"FastSwitchLanguage",
			FUIAction(FExecuteAction::CreateUObject(this, &UFastSwitchLanguage::ToggleSwitchLanguage)),
			TAttribute<FText>(),
			LOCTEXT("FastSwitchLanguage_ToolTip", "Toggle To Switch Language Between Chinese And English"),
			FSlateIcon(FDevCoreStyle::GetStyleSetName(), "Developer.FastSwitchLanguage", "Developer.FastSwitchLanguage.Small")
		)
	);
}

void UFastSwitchLanguage::ToggleSwitchLanguage()
{
	if (FInternationalization::Get().GetCurrentLanguage()->GetName() == "zh-Hans")
	{
		FInternationalization::Get().SetCurrentLanguage("en");
	}
	else if (FInternationalization::Get().GetCurrentLanguage()->GetName() == "en")
	{
		FInternationalization::Get().SetCurrentLanguage("zh-Hans");
	}
}

void UFastSwitchLanguage::RefreshBlueprints()
{
	UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
	TArray<UObject*> EditedAssets = AssetEditorSubsystem->GetAllEditedAssets();

	if (EditedAssets.Num() > 0)
	{
		for (UObject* Data : EditedAssets)
		{
			TWeakObjectPtr<UBlueprint> Blueprint = Cast<UBlueprint>(Data);
			FBlueprintEditorUtils::RefreshAllNodes(Blueprint.Get());
		}
	}
}

#undef LOCTEXT_NAMESPACE
