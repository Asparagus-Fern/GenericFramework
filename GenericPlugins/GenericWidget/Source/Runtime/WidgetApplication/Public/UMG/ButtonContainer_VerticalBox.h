// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericButtonContainer.h"
#include "ButtonContainer_VerticalBox.generated.h"

class UVerticalBoxSlot;
class UVerticalBox;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UButtonContainer_VerticalBox : public UGenericButtonContainer
{
	GENERATED_BODY()

protected:
	WIDGETAPPLICATION_API virtual void OnChildAdded_Implementation(UUserWidget* InWidget, int32 InIndex) override;
	WIDGETAPPLICATION_API virtual void OnChildRemoved_Implementation(UUserWidget* InWidget, int32 InIndex) override;

public:
	UPROPERTY(EditAnywhere, Category="Generic Button Container")
	float ButtonSpacing = 0.f;

	UPROPERTY(EditAnywhere, Category="Generic Button Container")
	FMargin ButtonPadding;

protected:
	WIDGETAPPLICATION_API virtual void UpdateVerticalBoxSlotPadding();
	WIDGETAPPLICATION_API virtual void UpdateVerticalBoxSlotPadding(UVerticalBoxSlot* InSlot, int32 SlotIndex);

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UVerticalBox> VerticalBox_ButtonContainer;
};
