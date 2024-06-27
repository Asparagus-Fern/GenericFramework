#pragma once

#include "CoreMinimal.h"
#include "Module/CommonModuleInterface.h"
#include "Modules/ModuleManager.h"

class FWorldPartitionModule : public ICommonModuleInterface
{
public:
	virtual void LoadDependentModule(TArray<FName>& InDependentModuleName) override;
};
