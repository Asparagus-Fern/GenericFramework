// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "GenericNavContent.generated.h"

class UGenericNavViewModel;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UGenericNavContent : public UGenericWidget
{
	GENERATED_BODY()

public:
	WIDGETGENERATION_API virtual void NativeConstruct() override;
	WIDGETGENERATION_API virtual void NativeDestruct() override;

public:
	UFUNCTION(BlueprintPure)
	WIDGETGENERATION_API UGenericNavViewModel* GetNavViewModel();

	UFUNCTION(BlueprintCallable)
	WIDGETGENERATION_API void SetNavViewModel(UGenericNavViewModel* InNavViewModel);

protected:
	UFUNCTION(BlueprintNativeEvent)
	WIDGETGENERATION_API void OnNavNumChanged(int32 InNum);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGENERATION_API void OnNavIndexChanged(int32 InIndex);

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UGenericNavViewModel> NavViewModel = nullptr;
};
