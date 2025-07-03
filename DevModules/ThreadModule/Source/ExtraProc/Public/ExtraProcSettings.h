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
class EXTRAPROC_API UExtraProcSettings : public UGenericSettings
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

#if WITH_EDITOR
	virtual FText GetSectionText() const override { return FText::FromString(TEXT("Extra Proc")); }
#endif

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="ExtraProc")
	TArray<FProcAutoStartUpInfo> AutoStartUpExtraProcList;
};
