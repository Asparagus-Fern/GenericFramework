#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FGenericMovieSceneSystemModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    
private:
    FDelegateHandle OnCreateMovieSceneUMGSpawnerDelegateHandle;

#if WITH_EDITOR
    FDelegateHandle EditorUMGSpawnerDelegateHandle;
    FDelegateHandle UMGTrackCreateEditorHandle;
#endif
};
