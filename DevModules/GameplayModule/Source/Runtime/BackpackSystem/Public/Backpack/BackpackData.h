// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "BackpackData.generated.h"

class UBackpackItemData;

/**
 * 
 */
UCLASS()
class BACKPACKSYSTEM_API UBackpackData : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category="Backpack")
	TArray<TObjectPtr<UBackpackItemData>> ItemList;
};
