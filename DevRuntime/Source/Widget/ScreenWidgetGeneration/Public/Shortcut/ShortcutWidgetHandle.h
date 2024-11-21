// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "ScreenWidgetType.h"
#include "Object/CommonObject.h"
#include "Procedure/ProcedureBaseInterface.h"
#include "ShortcutWidgetHandle.generated.h"

class UScreenWidgetManager;

/**
 * 处理UMG的快捷键操作
 */
UCLASS(Abstract)
class SCREENWIDGETGENERATION_API UShortcutWidgetHandle : public UCommonObject, public IProcedureBaseInterface
{
	GENERATED_BODY()

	friend UScreenWidgetManager;

protected:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;

protected:
	bool Equal(TSubclassOf<UUserWidgetBase> InWidgetClass) const;
	bool Equal(const UUserWidgetBase* InWidget) const;
	void Link(UUserWidgetBase* InWidget);
	void UnLink();

protected:
	UPROPERTY()
	UUserWidgetBase* Widget;

	UPROPERTY()
	FShortcutWidgetTableRow ShortcutWidgetTableRow;

protected:
	TArray<int32> BindingIndexArray;
	virtual void OnStarted(const FInputActionInstance& Instance);
	virtual void OnOngoing(const FInputActionInstance& Instance);
	virtual void OnTriggered(const FInputActionInstance& Instance);
	virtual void OnCanceled(const FInputActionInstance& Instance);
	virtual void OnCompleted(const FInputActionInstance& Instance);
};
