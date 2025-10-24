// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "GenericLoadingProgressBar.generated.h"

class UTextBlock;
class USpinBox;
class UGenericLoadingViewModel;

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericLoadingProgressBar : public UGenericWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	
public:
	UFUNCTION(BlueprintCallable)
	GENERICASSETLOADSYSTEM_API virtual void UpdatePerformance();

	UFUNCTION(BlueprintPure)
	GENERICASSETLOADSYSTEM_API UGenericLoadingViewModel* GetLoadingViewModel();

	UFUNCTION(BlueprintCallable)
	GENERICASSETLOADSYSTEM_API void SetLoadingViewModel(UGenericLoadingViewModel* InViewModel);

protected:
	UFUNCTION(BlueprintNativeEvent)
	GENERICASSETLOADSYSTEM_API void OnCurrentLoadingNumChanged(int32 InCurrentLoadingNum);

	UFUNCTION(BlueprintNativeEvent)
	GENERICASSETLOADSYSTEM_API void OnTotalLoadingNumChanged(int32 InCurrentLoadingNum);

	UFUNCTION(BlueprintNativeEvent)
	GENERICASSETLOADSYSTEM_API void GetLoadingText(float InValue, FText& Result);

	UPROPERTY()
	TObjectPtr<UGenericLoadingViewModel> LoadingViewModel = nullptr;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<USpinBox> SpinBox_Loading;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_Loading;
};
