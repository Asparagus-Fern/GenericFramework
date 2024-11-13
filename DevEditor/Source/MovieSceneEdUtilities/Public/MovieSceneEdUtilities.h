#pragma once

#include "CoreMinimal.h"
#include "Module/CommonEdModuleInterface.h"
#include "Modules/ModuleManager.h"

class FMovieSceneEdUtilitiesModule : public ICommonEdModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	FDelegateHandle EditorUMGSpawnerDelegateHandle;
	FDelegateHandle UMGTrackCreateEditorHandle;
};
