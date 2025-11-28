// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVM/Data/DataPropertyViewModel.h"
#include "TextPropertyViewModel.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYSYSTEM_API UTextPropertyViewModel : public UDataPropertyViewModel
{
	GENERATED_BODY()

public:
	virtual FString GetInitialValueAsString() override;
	virtual void SetInitialValueFromString(const FString& InValue) override;
	virtual FString GetCurrentValueAsString() override;
	virtual void SetCurrentValueFromString(const FString& InValue) override;

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	FText InitialValue;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	FText CurrentValue;
};
