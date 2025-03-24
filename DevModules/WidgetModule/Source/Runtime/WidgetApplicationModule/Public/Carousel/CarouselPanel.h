// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/UserWidgetBase.h"
#include "CarouselPanel.generated.h"

class UCommonWidgetCarousel;
class UCarouselNavBar;

/**
 * 
 */
UCLASS(MinimalAPI)
class UCarouselPanel : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	void HandleCarouselIndexChanged(int32 Index);

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonWidgetCarousel> CommonWidgetCarousel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCarouselNavBar> CarouselNavBar;
};
