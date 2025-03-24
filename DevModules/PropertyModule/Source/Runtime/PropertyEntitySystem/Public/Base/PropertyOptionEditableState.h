// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Common/CommonObject.h"
#include "PropertyOptionEditableState.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UPropertyOptionEditableState : public UCommonObject
{
	GENERATED_BODY()

public:
	UPropertyOptionEditableState(const FObjectInitializer& ObjectInitializer);

	TArray<FString> GetDisabledOptions() { return DisabledOptions; }
	TArray<FString> GetHiddenOptions() { return HiddenOptions; }

	void SetOptionEnabled(const FString& InOption, bool InEnabled);
	void SetOptionVisible(FString InOption, bool InVisible);

	template <typename EnumType>
	void SetEnumOptionEnabled(EnumType InEnumValue, bool InEnabled)
	{
		SetOptionEnabled(StaticEnum<EnumType>()->GetNameStringByValue((int64)InEnumValue), InEnabled);
	}

	template <typename EnumType>
	void SetEnumOptionVisible(EnumType InEnumValue, bool InVisible)
	{
		SetOptionVisible(StaticEnum<EnumType>()->GetNameStringByValue((int64)InEnumValue), InVisible);
	}

private:
	TArray<FString> DisabledOptions;
	TArray<FString> HiddenOptions;
};
