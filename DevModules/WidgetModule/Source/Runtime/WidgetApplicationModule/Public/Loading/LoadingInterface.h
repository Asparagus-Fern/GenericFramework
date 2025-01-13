// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LoadingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class ULoadingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WIDGETAPPLICATIONMODULE_API ILoadingInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category="Loading Interface")
	void OnLoadingBegin();
	virtual void NativeOnLoadingBegin(int32 Num);

	UFUNCTION(BlueprintNativeEvent, Category="Loading Interface")
	void OnLoadingOnceFinish();
	virtual void NativeOnLoadingOnceFinish();

	UFUNCTION(BlueprintNativeEvent, Category="Loading Interface")
	void OnLoadingEnd();
	virtual void NativeOnLoadingEnd();
};
