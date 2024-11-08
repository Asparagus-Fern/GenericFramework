#pragma once

#include "CoreMinimal.h"
#include "Module/CommonModuleInterface.h"
#include "Modules/ModuleManager.h"

class FMovieSceneUMGModuleModule : public ICommonModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
