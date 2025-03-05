// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UserWidgetBase.h"
#include "CarouselNavBar.generated.h"

class UCarouselContent;
class UInteractableWidgetBase;

/**
 * 
 */
UCLASS(MinimalAPI)
class UCarouselNavBar : public UUserWidgetBase
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
	void OnPreviewButtonClicked(UInteractableWidgetBase* InWidget);

	UFUNCTION()
	void OnNextButtonClicked(UInteractableWidgetBase* InWidget);

	void HandleCarouselChanged(int32 InNum, int32 InIndex);

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UInteractableWidgetBase> Button_Left;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = "CarouselContent", BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCarouselContent> CarouselContent;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UInteractableWidgetBase> Button_Right;
};
