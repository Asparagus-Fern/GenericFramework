#pragma once

#include "CoreMinimal.h"


/**
 *  
 */
class FDeveloperSettingCommands : public TCommands<FDeveloperSettingCommands>
{
public:
	FDeveloperSettingCommands();
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> OpenDeveloperSetting;
};
