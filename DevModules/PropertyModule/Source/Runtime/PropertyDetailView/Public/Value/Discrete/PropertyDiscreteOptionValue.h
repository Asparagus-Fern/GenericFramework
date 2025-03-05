// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteOptionValue.generated.h"

class FPropertyDataSource;

/**
 * 
 */
UCLASS()
class PROPERTYDETAILVIEW_API UPropertyDiscreteOption : public UPropertyEntity
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	FString GetOptionValue() const;

	UFUNCTION(BlueprintCallable)
	void SetOptionValue(FString InOptionValue);

protected:
	UPROPERTY(EditAnywhere, meta=(ExposeOnSpawn = true), Getter, Setter, BlueprintGetter="GetOptionValue", BlueprintSetter="SetOptionValue")
	FString OptionValue;
};

/**
 * 
 */
UCLASS()
class PROPERTYDETAILVIEW_API UPropertyDiscreteOptionValue : public UPropertyDiscreteValue
{
	GENERATED_BODY()

	/* UPropertyEntity */
protected:
	virtual void OnInitialized() override;
	virtual void GetChildProperties_Implementation(TArray<UPropertyEntity*>& Children) override;

public:
	bool HasOption(FName InOptionName);
	bool HasOption(int32 InOptionIndex);
	bool HasOption(UPropertyDiscreteOption* InOption);

	UPropertyDiscreteOption* GetOption(FName InOptionName);
	UPropertyDiscreteOption* GetOption(int32 InOptionIndex);

	UPropertyDiscreteOption* AddOption(FName InOptionName, FString InOptionValue, FText InOptionText, FText InOptionDescriptionText = FText::GetEmpty());

	void RemoveOption(FName InOptionName);
	void RemoveOption(int32 InOptionIndex);
	void RemoveOption(UPropertyDiscreteOption* InOption);

	TArray<UPropertyDiscreteOption*> GetOptions();

protected:
	UPROPERTY()
	TArray<TObjectPtr<UPropertyDiscreteOption>> Options;
};
