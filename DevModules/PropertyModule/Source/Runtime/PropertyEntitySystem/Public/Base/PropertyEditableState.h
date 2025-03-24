// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyOptionEditableState.h"
#include "Common/CommonObject.h"
#include "PropertyEditableState.generated.h"

class UPropertyOptionEditableState;

/**
 * 
 */
UCLASS(MinimalAPI)
class UPropertyEditableState : public UCommonObject
{
	GENERATED_BODY()

public:
	UPropertyEditableState(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure)
	bool IsVisible() const { return bVisible; }

	UFUNCTION(BlueprintPure)
	bool IsEnabled() const { return bEnabled; }

	UFUNCTION(BlueprintPure)
	bool IsResetable() const { return bResetable; }

	UFUNCTION(BlueprintCallable)
	void SetEnabled(bool InEnabled);

	UFUNCTION(BlueprintCallable)
	void SetVisible(bool InVisible);

	UFUNCTION(BlueprintCallable)
	void SetResetable(bool InResetable);

public:
	UFUNCTION(BlueprintCallable)
	void SetOptionEnabled(const FString& InOption, bool InEnabled);

	UFUNCTION(BlueprintCallable)
	void SetOptionVisible(FString InOption, bool InVisible);

	template <typename EnumType>
	void SetEnumOptionEnabled(EnumType InEnumValue, bool InEnabled)
	{
		OptionEditState->SetEnumOptionEnabled(InEnumValue, InEnabled);
	}

	template <typename EnumType>
	void SetEnumOptionVisible(EnumType InEnumValue, bool InVisible)
	{
		OptionEditState->SetEnumOptionVisible(InEnumValue, InVisible);
	}

	UFUNCTION(BlueprintPure)
	TArray<FString> GetDisabledOptions() const;

	UFUNCTION(BlueprintPure)
	TArray<FString> GetHiddenOptions() const;

private:
	uint8 bEnabled : 1;
	uint8 bVisible : 1;
	uint8 bResetable : 1;

	UPROPERTY()
	UPropertyOptionEditableState* OptionEditState = nullptr;
};
