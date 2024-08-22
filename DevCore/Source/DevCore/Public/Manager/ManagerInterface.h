// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ManagerInterface.generated.h"

class UManagerProxy;
/**
 * 
 */
UINTERFACE(MinimalAPI)
class UManagerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEVCORE_API IManagerInterface
{
	GENERATED_BODY()

public:
	virtual FText GetManagerDisplayName();
	virtual bool IsEditorManager();
	virtual bool DoesSupportWorldType(EWorldType::Type InWorldType);

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Procedure Interface")
	void OnBeginPlay();
	virtual void NativeOnBeginPlay();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Procedure Interface")
	void OnEndPlay();
	virtual void NativeOnEndPlay();
};
