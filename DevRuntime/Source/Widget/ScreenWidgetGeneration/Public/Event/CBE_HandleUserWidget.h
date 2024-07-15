// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonEvent.h"
#include "CBE_HandleUserWidget.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FOpenUserWidgetHandle
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bInstance = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "!bInstance"))
	TSubclassOf<UUserWidgetBase> WidgetClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, meta=(EditConditionHides, EditCondition = "bInstance"))
	UUserWidgetBase* Widget = nullptr;

public:
	UUserWidgetBase* GetOpenWidget() const;
};

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
class SCREENWIDGETGENERATION_API UCBE_HandleUserWidget : public UCommonButtonEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="OnActived")
	TArray<FOpenUserWidgetHandle> ActiveOpenWidgets;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="OnActived")
	TArray<FCloseUserWidgetHandle> ActiveCloseWidgets;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="OnInactived")
	TArray<FOpenUserWidgetHandle> InactiveOpenWidgets;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="OnInactived")
	TArray<FCloseUserWidgetHandle> InactiveCloseWidgets;

public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;
};
