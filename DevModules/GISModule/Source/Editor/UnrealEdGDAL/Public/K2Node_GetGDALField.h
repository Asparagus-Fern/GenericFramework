// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node_CallFunction.h"
#include "K2Node_GetGDALField.generated.h"

/**
 * 
 */
UCLASS()
class UNREALEDGDAL_API UK2Node_GetGDALField : public UK2Node_CallFunction
{
	GENERATED_BODY()

public:
	UK2Node_GetGDALField();

	/* UEdGraphNode */
public:
	virtual void AllocateDefaultPins() override;
	virtual FText GetTooltipText() const override;

	/* K2Node */
public:
	virtual bool IsNodePure() const override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& InActionRegistrar) const override;
	virtual FText GetMenuCategory() const override;
};
