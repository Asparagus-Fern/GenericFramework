#pragma once

#include "EnhancedInputSubsystemInterface.h"
#include "InputType.generated.h"

USTRUCT(BlueprintType)
struct FEnhanceInputMappingContext
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* InputMappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Priority = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FModifyContextOptions ModifyContextOptions;
};
