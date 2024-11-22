#include "UMGEdUtilities.h"

#include "Spline/UMGSplineDetailsCustomization.h"
#include "UWidget/UMGSpline.h"

#define LOCTEXT_NAMESPACE "FUMGEdUtilitiesModule"

void FUMGEdUtilitiesModule::StartupModule()
{
	ICommonEdModuleInterface::StartupModule();

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(UUMGSpline::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FUMGSplineDetailsCustomization::MakeInstance));

}

void FUMGEdUtilitiesModule::ShutdownModule()
{
	ICommonEdModuleInterface::ShutdownModule();

	if (!UObjectInitialized())
		return;

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomClassLayout(UUMGSpline::StaticClass()->GetFName());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUMGEdUtilitiesModule, UMGEdUtilities)
