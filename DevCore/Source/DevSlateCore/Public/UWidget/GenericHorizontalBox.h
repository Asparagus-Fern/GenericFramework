// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/HorizontalBox.h"
#include "GenericHorizontalBox.generated.h"

/**
 * 
 */
UCLASS()
class DEVSLATECORE_API UGenericHorizontalBox : public UHorizontalBox
{
	GENERATED_BODY()

public:
	virtual void OnSlotAdded(UPanelSlot* InSlot) override;
	virtual void OnSlotRemoved(UPanelSlot* InSlot) override;

public:
	UPROPERTY(EditAnywhere, Category="Generic Button Container")
	float Spacing = 0.f;
};
