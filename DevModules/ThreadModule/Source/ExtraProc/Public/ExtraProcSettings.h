// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ExtraProcType.h"
#include "Generic/GenericSettings.h"
#include "ExtraProcSettings.generated.h"

/**
 * 
 */
UCLASS()
class UExtraProcSettings : public UGenericSettings
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="ExtraProc")
	TArray<FProcAutoStartUpInfo> AutoStartUpExtraProcList;
};
