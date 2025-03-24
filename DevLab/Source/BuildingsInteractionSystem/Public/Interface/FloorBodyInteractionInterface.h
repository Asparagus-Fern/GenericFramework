// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FloorBodyInteractionInterface.generated.h"

class UFloorBodyComponent;

UINTERFACE()
class UFloorBodyInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BUILDINGSINTERACTIONSYSTEM_API IFloorBodyInteractionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category="Floor Body Interaction Interface")
	void HandleBeginCursorOverBody(UFloorBodyComponent* BodyComponent);

	UFUNCTION(BlueprintNativeEvent, Category="Floor Body Interaction Interface")
	void HandleEndCursorOverBody(UFloorBodyComponent* BodyComponent);

	UFUNCTION(BlueprintNativeEvent, Category="Floor Body Interaction Interface")
	void HandleBodyClicked(UFloorBodyComponent* BodyComponent);

	UFUNCTION(BlueprintNativeEvent, Category="Floor Body Interaction Interface")
	void HandleFloorSelectionChanged(bool bIsSelected);
	virtual void NativeHandleFloorSelectionChanged(bool bIsSelected);

protected:
	bool bIsFloorSelected = false;
};
