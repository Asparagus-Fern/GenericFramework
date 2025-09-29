// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LoadingInterface.h"
#include "Base/GenericWidget.h"
#include "LoadingPanel.generated.h"

class ULoadingProgressBar;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class ULoadingPanel : public UGenericWidget, public ILoadingInterface
{
	GENERATED_BODY()

	/* ILoadingInterface */
public:
	WIDGETAPPLICATION_API virtual void NativeOnLoadingBegin(int32 Num) override;
	WIDGETAPPLICATION_API virtual void NativeOnLoadingOnceFinish() override;
	WIDGETAPPLICATION_API virtual void NativeOnLoadingEnd() override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<ULoadingProgressBar> LoadingProgressBar;
};
