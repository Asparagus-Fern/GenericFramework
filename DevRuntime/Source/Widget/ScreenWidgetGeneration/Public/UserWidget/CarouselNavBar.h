// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "CarouselNavBar.generated.h"

class UCarouselContent;
class UInteractableUserWidgetBase;

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UCarouselNavBar : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UPROPERTY(EditAnywhere, meta=(ClampMin = 0, UIMin = 0))
	int32 Num = 0;

	UPROPERTY(EditAnywhere, meta=(ClampMin = 0, UIMin = 0))
	int32 DefaultIndex = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 Index = 0;

protected:
	UFUNCTION()
	void OnPreviewButtonClicked(UInteractableUserWidgetBase* InWidget);

	UFUNCTION()
	void OnNextButtonClicked(UInteractableUserWidgetBase* InWidget);

	UFUNCTION()
	void HandleNumChanged(int32 InNum);

	UFUNCTION()
	void HandleIndexChanged(int32 InIndex);

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UInteractableUserWidgetBase> Button_Left;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCarouselContent> CarouselContent;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UInteractableUserWidgetBase> Button_Right;
};
