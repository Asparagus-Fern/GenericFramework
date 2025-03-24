// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonObject.h"
#include "Interface/ProcedureBaseInterface.h"
#include "ViewportPanel.generated.h"

class SConstraintCanvas;
class UCanvasPanel;

/**
 * 
 */
UCLASS()
class DEVCORE_API UViewportPanel : public UCommonObject, public IProcedureBaseInterface
{
	GENERATED_BODY()

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnRefresh() override;
	virtual void NativeOnDestroy() override;

protected:
	virtual void HandleAddToViewport() PURE_VIRTUAL(UGamePanel::HandleAddToViewport,)
	virtual void HandleRemoveFromViewport() PURE_VIRTUAL(UGamePanel::HandleRemoveFromViewport,)

protected:
	/* 用于Game下的Panel */
	UPROPERTY()
	UCanvasPanel* CanvasPanel;

#if WITH_EDITOR
	TSharedPtr<SConstraintCanvas> ConstraintCanvas = nullptr;
#endif
};
