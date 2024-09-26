// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/CommonObject.h"
#include "PropertyEntity.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROPERTYDETAILVIEWSYSTEM_API UPropertyEntity : public UCommonObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	FName GetPropertyName() const;
	void SetPropertyName(FName InPropertyName);

	UFUNCTION(BlueprintPure)
	FText GetDisplayName() const;
	void SetDisplayName(const FText& InDisplayName);

	UFUNCTION(BlueprintPure)
	FText GetDescriptionText() const;
	void SetDescriptionText(const FText& InDescriptionText);

protected:
	FName PropertyName;
	FText DisplayName;
	FText DescriptionText;
};
