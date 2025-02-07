#include "MenuGenerationEditor.h"

#include "MenuCollectionCustomization.h"
#include "MenuEntityEventCustomization.h"

#define LOCTEXT_NAMESPACE "FMenuGenerationEditorModule"

void FMenuGenerationEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEditorModule.RegisterCustomClassLayout("MenuCollection", FOnGetDetailCustomizationInstance::CreateStatic(&FMenuCollectionCustomization::MakeInstance));
	PropertyEditorModule.RegisterCustomPropertyTypeLayout("MenuEntityEvent", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FMenuEntityEventCustomization::MakeInstance));
}

void FMenuGenerationEditorModule::ShutdownModule()
{
	if (FPropertyEditorModule* PropertyEditorModule = FModuleManager::GetModulePtr<FPropertyEditorModule>("PropertyEditor"))
	{
		PropertyEditorModule->UnregisterCustomClassLayout("MenuCollection");
		PropertyEditorModule->UnregisterCustomPropertyTypeLayout("MenuEntityEvent");
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMenuGenerationEditorModule, MenuGenerationEditor)
