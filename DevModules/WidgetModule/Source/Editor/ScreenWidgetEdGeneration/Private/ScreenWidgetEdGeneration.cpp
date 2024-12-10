#include "ScreenWidgetEdGeneration.h"

#include "UMGEditorProjectSettings.h"
#include "UserWidget/Base/InteractableUserWidgetBase.h"
#include "UserWidget/Base/UserWidgetBase.h"

#define LOCTEXT_NAMESPACE "FScreenWidgetEdGenerationModule"

void FScreenWidgetEdGenerationModule::StartupModule()
{
	UUMGEditorProjectSettings* UMGEditorProjectSettings = GetMutableDefault<UUMGEditorProjectSettings>();
	if (IsValid(UMGEditorProjectSettings))
	{
		if (!UMGEditorProjectSettings->FavoriteWidgetParentClasses.Contains(UUserWidgetBase::StaticClass()))
		{
			UMGEditorProjectSettings->FavoriteWidgetParentClasses.Add(UUserWidgetBase::StaticClass());
			UMGEditorProjectSettings->SaveConfig();
		}

		if (!UMGEditorProjectSettings->FavoriteWidgetParentClasses.Contains(UInteractableUserWidgetBase::StaticClass()))
		{
			UMGEditorProjectSettings->FavoriteWidgetParentClasses.Add(UInteractableUserWidgetBase::StaticClass());
			UMGEditorProjectSettings->SaveConfig();
		}
	}
}

void FScreenWidgetEdGenerationModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FScreenWidgetEdGenerationModule, ScreenWidgetEdGeneration)
