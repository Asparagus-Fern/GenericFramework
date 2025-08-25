// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "NumberFormattingOptionsViewModel.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew, MinimalAPI)
class UNumberFormattingOptionsViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	/* 在正数前也显示"+"号 */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	bool AlwaysSign = false;

	/* 是否使用千位分隔符 */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	bool UseGrouping = false;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ERoundingMode> RoundingMode = HalfToEven;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	int32 MinimumIntegralDigits = 1;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	int32 MaximumIntegralDigits = 256;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	int32 MinimumFractionalDigits = 3;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	int32 MaximumFractionalDigits = 3;
};
