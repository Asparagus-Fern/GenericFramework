// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "ButtonInputViewModel.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETGROUPGENERATION_API UButtonInputViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EButtonClickMethod::Type> ClickMethod = EButtonClickMethod::Type::DownAndUp;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EButtonTouchMethod::Type> TouchMethod = EButtonTouchMethod::Type::DownAndUp;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EButtonPressMethod::Type> PressMethod = EButtonPressMethod::Type::DownAndUp;
};
