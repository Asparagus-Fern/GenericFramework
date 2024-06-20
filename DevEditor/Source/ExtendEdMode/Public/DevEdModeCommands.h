#pragma once

#include "CoreMinimal.h"


/**
 * 
 */
class FDevEdModeCommands : public TCommands<FDevEdModeCommands>
{
public:
	FDevEdModeCommands();
	virtual void RegisterCommands() override;
	TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> GetCommands() const { return Commands; }

public:
	TSharedPtr<FUICommandInfo> DrawZoneShape;

protected:
	TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> Commands;
};
