// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Object/CommonObject.h"
#include "InputHandle.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS(Abstract, EditInlineNew)
class DEVCORE_API UInputHandle : public UCommonObject
{
	GENERATED_BODY()

public:
	UInputHandle();

public:
	UPROPERTY()
	UObject* Object = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<ETriggerEvent> TriggerEvents;

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnStarted(UObject* InObject, const FInputActionValue& InValue);
	void NativeOnStarted(const FInputActionValue& InValue);

	UFUNCTION(BlueprintNativeEvent)
	void Ongoing(UObject* InObject, const FInputActionValue& InValue);
	void NativeOngoing(const FInputActionValue& InValue);

	UFUNCTION(BlueprintNativeEvent)
	void OnTriggered(UObject* InObject, const FInputActionValue& InValue);
	void NativeOnTriggered(const FInputActionValue& InValue);

	UFUNCTION(BlueprintNativeEvent)
	void OnCanceled(UObject* InObject, const FInputActionValue& InValue);
	void NativeOnCanceled(const FInputActionValue& InValue);

	UFUNCTION(BlueprintNativeEvent)
	void OnCompleted(UObject* InObject, const FInputActionValue& InValue);
	void NativeOnCompleted(const FInputActionValue& InValue);
};
