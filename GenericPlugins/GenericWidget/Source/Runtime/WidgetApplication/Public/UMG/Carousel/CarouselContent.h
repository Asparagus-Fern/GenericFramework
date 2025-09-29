// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "CarouselContent.generated.h"

class UCommonButtonGroup;
class UGenericButtonWidget;
/**
 * 
 */
UCLASS(MinimalAPI)
class UCarouselContent : public UGenericWidget
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
	DECLARE_EVENT_TwoParams(UCarouselContent, FOnCarouselChanged, int32, int32);

	FOnCarouselChanged OnCarouselChanged;

protected:
	UPROPERTY(BlueprintReadOnly)
	int32 Num;

	UPROPERTY(BlueprintReadOnly)
	int32 Index;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnCarouselChanged(int32 InNum, int32 InIndex);
};
