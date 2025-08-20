// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "GameSettingViewModel.generated.h"

class UQualitySettingViewModel;

/**
 * 
 */
UCLASS()
class GAMESETTINGSYSTEM_API UGameSettingViewModel : public UMVVMViewModelBase
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintPure)
	static TArray<FString> GetQualityStringName();

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0, UIMin = 0, ClampMax = 4, UIMax = 4))
	TObjectPtr<UQualitySettingViewModel> QualitySettings;
};
