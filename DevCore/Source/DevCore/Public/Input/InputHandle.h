// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Object/CommonObject.h"
#include "InputHandle.generated.h"

class UCommonInputComponent;
class UInputAction;

/**
 * 
 */
UCLASS(Abstract, EditInlineNew)
class DEVCORE_API UInputHandle : public UCommonObject
{
	GENERATED_BODY()

	friend UCommonInputComponent;

public:
	UInputHandle();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<ETriggerEvent> TriggerEvents;

protected:
	UPROPERTY()
	UObject* Object = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UCommonInputComponent* InputComponent = nullptr;

protected:
	void SetupInputMapping(UObject* InObject, UCommonInputComponent* InInputComponent);
	void ClearupInputMapping();

protected:
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

protected:
	TArray<uint32> Handles;
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct DEVCORE_API FPlayerInputHandle
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<UInputHandle> InputHandleClass = nullptr;
};
