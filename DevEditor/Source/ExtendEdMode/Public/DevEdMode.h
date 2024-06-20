#pragma once

#include "CoreMinimal.h"
#include "Tools/UEdMode.h"
#include "DevEdMode.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDMODE_API UDevEdMode : public UEdMode
{
	GENERATED_BODY()

public:
	static FEditorModeID DevCommonEdModeId;

	UDevEdMode();

	/* UEdMode */
public:
	virtual void Enter() override;
	virtual void CreateToolkit() override;
	virtual TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> GetModeCommands() const override;
};
