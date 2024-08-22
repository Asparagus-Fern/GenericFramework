#pragma once

#include "CoreMinimal.h"
#include "Module/CommonEdModuleInterface.h"

class FManagerVisualizationModule : public ICommonEdModuleInterface
{
protected:
	virtual void RegisterCommand() override;
	virtual void UnRegisterCommand() override;
};
