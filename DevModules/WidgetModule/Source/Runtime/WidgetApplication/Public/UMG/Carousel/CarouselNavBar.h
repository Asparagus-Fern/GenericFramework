// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "CarouselNavBar.generated.h"

class UCarouselContent;
class UGenericButtonWidget;

/**
 * 
 */
UCLASS(MinimalAPI)
class UCarouselNavBar : public UGenericWidget
{
	GENERATED_BODY()

public:
	WIDGETAPPLICATION_API virtual void NativePreConstruct() override;
	WIDGETAPPLICATION_API virtual void NativeConstruct() override;
	WIDGETAPPLICATION_API virtual void NativeDestruct() override;

public:
	UFUNCTION(BlueprintCallable)
	WIDGETAPPLICATION_API void SetNum(int32 InNum);

	UFUNCTION(BlueprintCallable)
	WIDGETAPPLICATION_API void SetIndex(int32 InIndex);

public:
	DECLARE_EVENT_OneParam(UCarouselNavBar, FOnCarouselIndexChanged, int32);

	FOnCarouselIndexChanged OnCarouselIndexChanged;

protected:
	UPROPERTY(EditAnywhere, meta=(ClampMin = 0, UIMin = 0))
	int32 Num = 0;

	UPROPERTY(EditAnywhere, meta=(ClampMin = 0, UIMin = 0))
	int32 DefaultIndex = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 Index = 0;

	UPROPERTY(BlueprintReadWrite)
	bool bAllowWrap = true;

protected:
	UFUNCTION()
	WIDGETAPPLICATION_API void OnPreviewButtonClicked(UGenericButtonWidget* InWidget);

	UFUNCTION()
	WIDGETAPPLICATION_API void OnNextButtonClicked(UGenericButtonWidget* InWidget);

	WIDGETAPPLICATION_API void HandleCarouselChanged(int32 InNum, int32 InIndex);

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericButtonWidget> Button_Left;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = "CarouselContent", BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCarouselContent> CarouselContent;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericButtonWidget> Button_Right;
};
