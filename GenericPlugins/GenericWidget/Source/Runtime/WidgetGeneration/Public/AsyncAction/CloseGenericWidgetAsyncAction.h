// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CloseGenericWidgetAsyncAction.generated.h"

class UGenericWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCloseUserWidgetDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUserWidgetInactivedAnimationDelegate);

/**
 * 
 */
UCLASS()
class WIDGETGENERATION_API UCloseGenericWidgetAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

public:
	UFUNCTION(BlueprintCallable, DisplayName="Close Generic Widget By Tag", meta = (WorldContext = "InWorldContextObject", GameplayTagFilter="UI.HUD", BlueprintInternalUseOnly = "true", AdvancedDisplay = 1))
	static UCloseGenericWidgetAsyncAction* AsyncCloseGenericWidgetByTag(UObject* InWorldContextObject, FGameplayTag InSlotTag, bool MarkAsGarbage = true);

	UFUNCTION(BlueprintCallable, DisplayName="Close Generic Widget", meta = (WorldContext = "InWorldContextObject", BlueprintInternalUseOnly = "true", AdvancedDisplay = 2))
	static UCloseGenericWidgetAsyncAction* AsyncCloseGenericWidget(UObject* InWorldContextObject, UGenericWidget* InWidget, bool MarkAsGarbage = true);

public:
	UPROPERTY(BlueprintAssignable)
	FOnUserWidgetInactivedAnimationDelegate OnAnimationFinish;

	UPROPERTY(BlueprintAssignable)
	FCloseUserWidgetDelegate OnFinish;

private:
	virtual void OnWidgetInactived(UGenericWidget* InWidget);
	virtual void OnWidgetInactivedAnimationFinish(UGenericWidget* InWidget);

	UPROPERTY()
	UObject* WorldContextObject = nullptr;

	UPROPERTY()
	TObjectPtr<UGenericWidget> Widget;

	bool bMarkAsGarbage = false;
};
