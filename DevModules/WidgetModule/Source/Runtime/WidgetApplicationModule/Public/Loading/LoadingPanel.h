// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoadingInterface.h"
#include "Base/UserWidgetBase.h"
#include "LoadingPanel.generated.h"

class ULoadingProgressBar;

/**
 * 
 */
UCLASS(Abstract)
class WIDGETAPPLICATIONMODULE_API ULoadingPanel : public UUserWidgetBase, public ILoadingInterface
{
	GENERATED_BODY()

	/* ILoadingInterface */
public:
	virtual void NativeOnLoadingBegin(int32 Num) override;
	virtual void NativeOnLoadingOnceFinish() override;
	virtual void NativeOnLoadingEnd() override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<ULoadingProgressBar> LoadingProgressBar;
};
