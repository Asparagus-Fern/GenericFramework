#include "WidgetGeneration.h"

#include "Base/GenericWidget.h"

#if WITH_EDITOR
#include "UMGEditorProjectSettings.h"
#endif

#define LOCTEXT_NAMESPACE "FWidgetGenerationModule"

void FWidgetGenerationModule::StartupModule()
{
#if WITH_EDITOR
	UUMGEditorProjectSettings* UMGEditorProjectSettings = GetMutableDefault<UUMGEditorProjectSettings>();
	if (IsValid(UMGEditorProjectSettings))
	{
		if (!UMGEditorProjectSettings->FavoriteWidgetParentClasses.Contains(UGenericWidget::StaticClass()))
		{
			UMGEditorProjectSettings->FavoriteWidgetParentClasses.Add(UGenericWidget::StaticClass());
			UMGEditorProjectSettings->SaveConfig();
		}
	}
#endif
}

void FWidgetGenerationModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWidgetGenerationModule, WidgetGeneration)
