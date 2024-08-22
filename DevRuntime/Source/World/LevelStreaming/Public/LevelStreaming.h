#pragma once

#include "CoreMinimal.h"
#include "Module/CommonModuleInterface.h"
#include "Modules/ModuleManager.h"

class FLevelStreamingModule : public ICommonModuleInterface
{
public:
	virtual void LoadDependentModule(TArray<FName>& InDependentModuleName) override;
};
