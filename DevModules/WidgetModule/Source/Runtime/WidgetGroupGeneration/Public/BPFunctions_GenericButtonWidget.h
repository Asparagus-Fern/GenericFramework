// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_GenericButtonWidget.generated.h"

class UGenericButtonCollection;

/**
 * 
 */
UCLASS()
class WIDGETGROUPGENERATION_API UBPFunctions_GenericButtonWidget : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "InCollectionClass"))
	static UGenericButtonCollection* RegisterButtonCollectionByClass(TSubclassOf<UGenericButtonCollection> InCollectionClass, bool InActived = true);

	UFUNCTION(BlueprintCallable)
	static bool RegisterButtonCollection(UGenericButtonCollection* InCollection, bool InActived = true);

	UFUNCTION(BlueprintCallable)
	static bool UnRegisterButtonCollection(UGenericButtonCollection* InCollection);
};
