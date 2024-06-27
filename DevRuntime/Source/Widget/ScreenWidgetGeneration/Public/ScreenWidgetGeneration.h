#pragma once

#include "CoreMinimal.h"
#include "Module/CommonModuleInterface.h"
/**
 * 
 */
class FScreenWidgetGenerationModule : public ICommonModuleInterface
{
public:
	virtual void GetRegisterManager(TArray<TSubclassOf<UCoreManager>>& InRegisterManagerClasses) override;
};
