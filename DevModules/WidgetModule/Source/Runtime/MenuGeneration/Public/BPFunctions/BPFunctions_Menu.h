// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Menu.generated.h"

class UMenuCollection;

/**
 * 
 */
UCLASS()
class MENUGENERATION_API UBPFunctions_Menu : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "InCollectionClass"))
	static UMenuCollection* RegisterMenuCollectionByClass(TSubclassOf<UMenuCollection> InCollectionClass, bool InActived = true);

	UFUNCTION(BlueprintCallable)
	static bool RegisterMenuCollection(UMenuCollection* InCollection, bool InActived = true);

	UFUNCTION(BlueprintCallable)
	static bool UnRegisterMenuCollection(UMenuCollection* InCollection);
};
