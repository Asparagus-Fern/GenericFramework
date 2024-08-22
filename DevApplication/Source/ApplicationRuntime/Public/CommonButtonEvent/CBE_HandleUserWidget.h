// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_HandleUserWidget.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCloseUserWidgetHandle
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidgetBase> CloseWidgetClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="HUD"))
	FGameplayTag SlotTag;

public:
	FGameplayTag GetCloseWidgetSlotTag() const;
};

/**
 * 处理Widget的打开或关闭
 */
UCLASS()
class APPLICATIONRUNTIME_API UCBE_HandleUserWidget : public UCommonButtonEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="OnActived")
	TArray<FWidgetContainer> ActiveOpenWidgets;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="OnActived")
	TArray<FCloseUserWidgetHandle> ActiveCloseWidgets;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="OnInactived")
	TArray<FWidgetContainer> InactiveOpenWidgets;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="OnInactived")
	TArray<FCloseUserWidgetHandle> InactiveCloseWidgets;

public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;
};
