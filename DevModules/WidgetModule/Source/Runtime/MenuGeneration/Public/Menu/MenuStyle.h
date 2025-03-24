// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractableWidgetBase.h"
#include "MenuStyle.generated.h"

class UMenuEntityBase;

/**
 * 
 */
UCLASS(BlueprintType, MinimalAPI)
class UMenuStyle : public UInteractableWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void ConstructMenuStyle();
	virtual void NativeConstructMenuStyle();

	UFUNCTION(BlueprintPure)
	UMenuEntityBase* GetMenuEntityBase();
};
