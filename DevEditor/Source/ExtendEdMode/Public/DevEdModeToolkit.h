#pragma once

#include "CoreMinimal.h"
#include "Toolkits/BaseToolkit.h"

/**
 * 
 */
class FDevEdModeToolkit : public FModeToolkit
{
	/* FModeToolkit */
public:
	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost) override;
	virtual void GetToolPaletteNames(TArray<FName>& PaletteNames) const override;

	/* IToolkit Interface */
public:
	virtual FName GetToolkitFName() const override;
	virtual FText GetToolkitName() const override;

	virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;
	virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;

protected:
	TSharedPtr<SWidget> ViewportWidget;

	virtual TSharedRef<SWidget> MakeEdModeViewportWidget();
};
