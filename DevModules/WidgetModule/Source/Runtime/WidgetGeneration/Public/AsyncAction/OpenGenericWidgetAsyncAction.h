// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "OpenGenericWidgetAsyncAction.generated.h"

class UGenericWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOpenUserWidgetDelegate, UGenericWidget*, Widget);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUserWidgetActivedAnimationDelegate);

/**
 * 
 */
UCLASS()
class WIDGETGENERATION_API UOpenGenericWidgetAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;
	
public:
	UFUNCTION(BlueprintCallable, DisplayName="Open Generic Widget", meta = (BlueprintInternalUseOnly = "true"))
	static UOpenGenericWidgetAsyncAction* AsyncOpenGenericWidget( UGenericWidget* InWidget);

public:
	UPROPERTY(BlueprintAssignable)
	FOpenUserWidgetDelegate OnFinish;

	UPROPERTY(BlueprintAssignable)
	FOnUserWidgetActivedAnimationDelegate OnAnimationFinish;

private:
	virtual void OnWidgetActived(UGenericWidget* InWidget);
	virtual void OnWidgetActivedAnimationFinish(UGenericWidget* InWidget);

	UPROPERTY()
	TObjectPtr<UGenericWidget> Widget;
};
