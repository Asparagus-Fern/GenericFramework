#pragma once

#include "CoreMinimal.h"
#include "Module/CommonEdModuleInterface.h"

class FWorldWidgetEdGenerationModule : public ICommonEdModuleInterface
{
protected:
	virtual void LoadDependentModule(TArray<FName>& InDependentModuleName) override;
};
