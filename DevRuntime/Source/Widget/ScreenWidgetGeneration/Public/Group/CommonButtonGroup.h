// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Groups/CommonButtonGroupBase.h"
#include "CommonButtonGroup.generated.h"

class UScreenWidgetManager;

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UCommonButtonGroup : public UCommonButtonGroupBase
{
	GENERATED_BODY()

	friend UScreenWidgetManager;

	/* UCommonButtonGroupBase */
public:
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetSelectionRequiredIndex", BlueprintSetter="SetSelectionRequiredIndex")
	int32 SelectionRequiredIndex = 0;

public:
	UFUNCTION(BlueprintPure)
	int32 GetSelectionRequiredIndex() const;

	UFUNCTION(BlueprintCallable)
	void SetSelectionRequiredIndex(int32 InIndex);

	UFUNCTION(BlueprintCallable)
	void UpdateSelectionRequired(bool bRequireSelection);
};
