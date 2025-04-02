#include "DevEdCore.h"

#include "UWidget/Spline2D.h"
#include "Widget/Spline2D/Spline2DDetailsCustomization.h"

#define LOCTEXT_NAMESPACE "FDevEdCoreModule"

void FDevEdCoreModule::StartupModule()
{
	IModuleInterface::StartupModule();

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(USpline2D::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FSpline2DDetailsCustomization::MakeInstance));
}

void FDevEdCoreModule::ShutdownModule()
{
	IModuleInterface::ShutdownModule();

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomClassLayout(USpline2D::StaticClass()->GetFName());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDevEdCoreModule, DevEdCore)
