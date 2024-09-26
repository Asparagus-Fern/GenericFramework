#include "ApplicationDeveloper.h"

#include "EdGraphUtilities.h"
#include "K2Node/FBlueprintGraphPanelPinExtendFactory.h"

#define LOCTEXT_NAMESPACE "FApplicationDeveloperModule"

void FApplicationDeveloperModule::StartupModule()
{
	/* 注册K2Node扩展 */
	const TSharedPtr<FBlueprintGraphPanelPinExtendFactory> BlueprintGraphPanelPinExtendFactory = MakeShareable(new FBlueprintGraphPanelPinExtendFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(BlueprintGraphPanelPinExtendFactory);
}

void FApplicationDeveloperModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FApplicationDeveloperModule, ApplicationDeveloper)