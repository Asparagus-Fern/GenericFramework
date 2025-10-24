// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GenericWindowContent.h"
#include "GenericMessageDialog.generated.h"

class UGenericButtonWidget;
class UHorizontalBox;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageDialogSubmit, FGameplayTag, Result);

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UGenericMessageDialog : public UGenericWindowContent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	FGameplayTag GetResultDialogType() const;

	UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="Result"))
	WINDOWGENERATION_API void SubmitMessageDialogResult(FGameplayTag InDialogType);

protected:
	UPROPERTY()
	FGameplayTag ResultDialogType;
};
