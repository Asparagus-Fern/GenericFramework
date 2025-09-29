// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "CarouselPanel.generated.h"

class UCommonWidgetCarousel;
class UCarouselNavBar;

/**
 * 
 */
UCLASS(MinimalAPI)
class UCarouselPanel : public UGenericWidget
{
	GENERATED_BODY()

public:
	WIDGETAPPLICATION_API virtual void NativePreConstruct() override;
	WIDGETAPPLICATION_API virtual void NativeConstruct() override;
	WIDGETAPPLICATION_API virtual void NativeDestruct() override;

protected:
	WIDGETAPPLICATION_API void HandleCarouselIndexChanged(int32 Index);

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonWidgetCarousel> CommonWidgetCarousel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCarouselNavBar> CarouselNavBar;
};
