#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FGenericMovieSceneEdSystemModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	FDelegateHandle EditorUMGSpawnerDelegateHandle;
	FDelegateHandle UMGTrackCreateEditorHandle;
};
