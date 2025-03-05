// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UserWidgetBase.h"
#include "CarouselContent.generated.h"

class UCommonButtonGroup;
class UInteractableWidgetBase;
/**
 * 
 */
UCLASS(MinimalAPI)
class UCarouselContent : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetNum(int32 InNum);

	UFUNCTION(BlueprintCallable)
	void SetIndex(int32 InIndex);

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
