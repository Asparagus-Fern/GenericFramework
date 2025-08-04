#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FMovieSceneExtendModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	FDelegateHandle OnCreateMovieSceneUMGSpawnerDelegateHandle;

#if WITH_EDITOR

private:
	FDelegateHandle EditorUMGSpawnerDelegateHandle;
	FDelegateHandle UMGTrackCreateEditorHandle;

#endif
};
