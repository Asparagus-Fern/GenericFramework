// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "GenericLoadingViewModel.generated.h"

/**
 * 
 */
UCLASS()
class GENERICASSETLOADSYSTEM_API UGenericLoadingViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	float GetLoadingValue();

	UFUNCTION(BlueprintCallable)
	float GetLoadingPercentage();

public:
	/* 当前以加载个数 */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	int32 CurrentLoadingNum = 0;

	/* 需加载总数 */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	int32 TotalLoadingNum = 0;
};
