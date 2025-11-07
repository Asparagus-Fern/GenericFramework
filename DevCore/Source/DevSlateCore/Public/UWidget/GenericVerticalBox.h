// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/VerticalBox.h"
#include "GenericVerticalBox.generated.h"

/**
 * 
 */
UCLASS()
class DEVSLATECORE_API UGenericVerticalBox : public UVerticalBox
{
	GENERATED_BODY()

public:
	virtual void OnSlotAdded(UPanelSlot* InSlot) override;
	virtual void OnSlotRemoved(UPanelSlot* InSlot) override;

public:
	UPROPERTY(EditAnywhere, Category="Generic Button Container")
	float ButtonSpacing = 0.f;
};
