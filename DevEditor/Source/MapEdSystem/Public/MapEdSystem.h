#pragma once

#include "CoreMinimal.h"
#include "Module/CommonEdModuleInterface.h"

class FMapEdSystemModule : public ICommonEdModuleInterface
{
public:
	virtual void StartupModule() override;
};
