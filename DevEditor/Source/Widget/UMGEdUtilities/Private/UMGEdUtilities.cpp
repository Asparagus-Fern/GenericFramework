#include "UMGEdUtilities.h"

#include "Spline/UMGSplineDetailsCustomization.h"
#include "UWidget/Spline2D.h"

#define LOCTEXT_NAMESPACE "FUMGEdUtilitiesModule"

void FUMGEdUtilitiesModule::StartupModule()
{
	ICommonEdModuleInterface::StartupModule();

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(USpline2D::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FUMGSplineDetailsCustomization::MakeInstance));

}

void FUMGEdUtilitiesModule::ShutdownModule()
{
	ICommonEdModuleInterface::ShutdownModule();

	if (!UObjectInitialized())
		return;

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomClassLayout(USpline2D::StaticClass()->GetFName());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUMGEdUtilitiesModule, UMGEdUtilities)
