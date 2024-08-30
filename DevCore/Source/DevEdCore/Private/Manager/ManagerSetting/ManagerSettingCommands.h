#pragma once

#include "CoreMinimal.h"


/**
 *  
 */
class FManagerSettingCommands : public TCommands<FManagerSettingCommands>
{
public:
	FManagerSettingCommands();
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> OpenManagerSetting;
};
