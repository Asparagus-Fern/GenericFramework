// Copyright ChenTaiye 2025. All Rights Reserved.

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
