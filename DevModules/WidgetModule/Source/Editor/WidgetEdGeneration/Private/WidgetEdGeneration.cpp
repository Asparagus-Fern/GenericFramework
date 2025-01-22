#include "WidgetEdGeneration.h"

#include "UMGEditorProjectSettings.h"
#include "Base/UserWidgetBase.h"
#include "Spline/UMGSplineDetailsCustomization.h"
#include "UWidget/Spline2D.h"

#define LOCTEXT_NAMESPACE "FWidgetEdGenerationModule"

void FWidgetEdGenerationModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(USpline2D::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FUMGSplineDetailsCustomization::MakeInstance));

	UUMGEditorProjectSettings* UMGEditorProjectSettings = GetMutableDefault<UUMGEditorProjectSettings>();
	if (IsValid(UMGEditorProjectSettings))
	{
		if (!UMGEditorProjectSettings->FavoriteWidgetParentClasses.Contains(UUserWidgetBase::StaticClass()))
		{
			UMGEditorProjectSettings->FavoriteWidgetParentClasses.Add(UUserWidgetBase::StaticClass());
			UMGEditorProjectSettings->SaveConfig();
		}
	}
}

void FWidgetEdGenerationModule::ShutdownModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomClassLayout(USpline2D::StaticClass()->GetFName());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWidgetEdGenerationModule, WidgetEdGeneration)
