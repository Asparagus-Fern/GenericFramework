// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WidgetEntityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UWidgetEntityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WIDGETGENERATION_API IWidgetEntityInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Widget Entity Interface")
	void OpenEntityWidget();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Widget Entity Interface")
	void CloseEntityWidget();
};
