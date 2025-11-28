#include "ApplicationEditor.h"

#include "ApplicationTestActor.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "GameDelegates.h"
#include "NiagaraSettings.h"
#include "NiagaraSimCacheCapture.h"
#include "Widgets/Layout/SUniformGridPanel.h"

#define LOCTEXT_NAMESPACE "FApplicationEditorModule"

void FApplicationEditorModule::StartupModule()
{
}

void FApplicationEditorModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FApplicationEditorModule, ApplicationEditor)
