#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "GenericLoadingScreen.generated.h"

class UGenericLoadingScreenViewModel;
/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UGenericLoadingScreen : public UGenericWidget
{
	GENERATED_BODY()

protected:
	WIDGETAPPLICATION_API virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	WIDGETAPPLICATION_API void SetLoadCount(int32 InLoadCount);
	WIDGETAPPLICATION_API void NotifyLoadOnceFinish();

	UFUNCTION(BlueprintPure)
	WIDGETAPPLICATION_API UGenericLoadingScreenViewModel* GetLoadingScreenViewModel() const;

	UFUNCTION(BlueprintNativeEvent)
	WIDGETAPPLICATION_API void SetLoadingScreenViewModel(UGenericLoadingScreenViewModel* InViewModel);

	UFUNCTION(BlueprintPure)
	WIDGETAPPLICATION_API bool GetIsFinished() const;

	FSimpleMulticastDelegate OnLoadFinishedEvent;

protected:
	UFUNCTION(BlueprintNativeEvent)
	WIDGETAPPLICATION_API void OnTargetPercentageChanged(float Percentage);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETAPPLICATION_API void OnLoadFinished();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UGenericLoadingScreenViewModel> LoadingScreenViewModel = nullptr;

	bool bFinishLoad = false;
	int32 LoadCount = 0;
	int32 CurrentLoadCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float LoadPercentage = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TargetLoadPercentage = 0.f;
};
