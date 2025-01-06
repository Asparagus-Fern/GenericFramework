// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonObject.h"
#include "Procedure/ProcedureBaseInterface.h"
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
