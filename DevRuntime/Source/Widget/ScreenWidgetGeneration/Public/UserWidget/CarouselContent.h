// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UserWidgetBase.h"
#include "CarouselContent.generated.h"

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UCarouselContent : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetNum(int32 InNum);

	UFUNCTION(BlueprintCallable)
	void SetIndex(int32 InIndex);

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNumChanged, int32, Num);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIndexChanged, int32, Index);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnNumChanged OnNumChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnIndexChanged OnIndexChanged;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnNumChanged(int32 InNum);

	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnIndexChanged(int32 InIndex);
};
