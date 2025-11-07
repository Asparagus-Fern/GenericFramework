// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GenericWidget.h"
#include "GenericPopupWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnPopupResultSubmitted, FGameplayTag)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnPopupResultSubmitted, FGameplayTag, InPopupResult);

/**
 * Popup Widget Will Disable All Input Which All Widgets In Game Slot
 * Only Useful In The Slot : UI.HUD.Popup
 */
UCLASS(MinimalAPI)
class UGenericPopupWidget : public UGenericWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	WIDGETGENERATION_API FGameplayTag GetPopupResult() const;

	UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="Result"))
	WIDGETGENERATION_API void SubmitPopupResult(FGameplayTag InPopupResult);

	FDelegate_OnPopupResultSubmitted Delegate_OnPopupResultSubmitted;
	UPROPERTY(BlueprintAssignable, meta=(Categories="Result"))
	FBPDelegate_OnPopupResultSubmitted BPDelegate_OnPopupResultSubmitted;

protected:
	UFUNCTION(BlueprintNativeEvent)
	WIDGETGENERATION_API void OnErrorPopupResultSubmitted(FGameplayTag InPopupResult);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGENERATION_API void OnPopupResultSubmitted(FGameplayTag InPopupResult);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bBreakGameInput = false;

private:
	UPROPERTY()
	FGameplayTag PopupResult;
};
