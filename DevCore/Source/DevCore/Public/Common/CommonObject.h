// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Debug/DebugType.h"
#include "UObject/Object.h"
#include "CommonObject.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class DEVCORE_API UCommonObject : public UObject
{
	GENERATED_BODY()

public:
	UCommonObject(const FObjectInitializer& ObjectInitializer);
	virtual UWorld* GetWorld() const override;
	virtual void BeginDestroy() override;

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnInitialized();
	virtual void NativeInitialize();

	UFUNCTION(BlueprintNativeEvent)
	void OnDeInitialized();
	virtual void NativeDeInitialize();
};

// template <class T>
// FUNCTION_NON_NULL_RETURN_START
// T* NewCommonObject(UObject* Outer = (UObject*)GetTransientPackage())
// FUNCTION_NON_NULL_RETURN_END
// {
// 	T* Object = NewObject<T>(Outer);
// 	if (UCommonObject* CommonObject = Cast<UCommonObject>(Object))
// 	{
// 		CommonObject->NativeInitialize();
// 		CommonObject->OnInitialized();
// 		DLOG(DLogObject, Log, TEXT("On Initialize : %s"), *CommonObject->GetName());
// 	}
//
// 	return Object;
// }
