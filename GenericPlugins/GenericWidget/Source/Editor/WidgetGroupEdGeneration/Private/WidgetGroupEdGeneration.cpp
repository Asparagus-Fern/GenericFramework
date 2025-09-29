#include "WidgetGroupEdGeneration.h"

#include "GenericButtonCollectionCustomization.h"

#define LOCTEXT_NAMESPACE "FWidgetGroupEdGenerationModule"

void FWidgetGroupEdGenerationModule::StartupModule()
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEditorModule.RegisterCustomClassLayout("GenericButtonCollection", FOnGetDetailCustomizationInstance::CreateStatic(&FGenericButtonCollectionCustomization::MakeInstance));
}

void FWidgetGroupEdGenerationModule::ShutdownModule()
{
	if (FPropertyEditorModule* PropertyEditorModule = FModuleManager::GetModulePtr<FPropertyEditorModule>("PropertyEditor"))
	{
		PropertyEditorModule->UnregisterCustomClassLayout("GenericButtonCollection");
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWidgetGroupEdGenerationModule, WidgetGroupEdGeneration)
