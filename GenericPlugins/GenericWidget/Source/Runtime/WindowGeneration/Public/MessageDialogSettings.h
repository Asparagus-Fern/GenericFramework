// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Generic/GenericSettings.h"
#include "MessageDialogSettings.generated.h"

class UGenericWindowViewModel;
/**
 * 
 */
UCLASS()
class UMessageDialogSettings : public UGenericSettings
{
	GENERATED_UCLASS_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<UGenericWindowViewModel> MessageDialogWindowClass = nullptr;
};
