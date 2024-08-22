#pragma once

#include "CoreMinimal.h"
#include "Module/CommonModuleInterface.h"

class FWorldWidgetGenerationModule : public ICommonModuleInterface
{
public:
	virtual void LoadDependentModule(TArray<FName>& InDependentModuleName) override;
};
