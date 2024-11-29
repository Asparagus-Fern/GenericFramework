// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoadingInterface.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "Loading.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SCREENWIDGETGENERATION_API ULoading : public UUserWidgetBase, public ILoadingInterface
{
	GENERATED_BODY()

	/* ILoadingInterface */
public:
	virtual void NativeOnLoadingBegin(int32 Num) override;
	virtual void NativeOnLoadingOnceFinish() override;
	virtual void NativeOnLoadingEnd() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentLoadingNum = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 LoadingNum = 0;
	
	UPROPERTY(BlueprintReadOnly)
	float LoadingPercentage = 0.f;
};
