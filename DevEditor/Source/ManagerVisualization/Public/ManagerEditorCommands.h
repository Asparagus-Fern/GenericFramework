#pragma once

#include "CoreMinimal.h"


/**
 * 
 */
class FManagerEditorCommands : public TCommands<FManagerEditorCommands>
{
public:
	FManagerEditorCommands();
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> OpenManagerEditor;
};
