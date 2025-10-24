// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "GenericNavBar.generated.h"

class UGenericButton;
class UGenericNavViewModel;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UGenericNavBar : public UGenericWidget
{
	GENERATED_BODY()

public:
	WIDGETAPPLICATION_API virtual void NativeConstruct() override;
	WIDGETAPPLICATION_API virtual void NativeDestruct() override;

private:
	UFUNCTION()
	void SwitchLeft();

	UFUNCTION()
	void SwitchRight();

public:
	UFUNCTION(BlueprintPure)
	WIDGETAPPLICATION_API UGenericNavViewModel* GetNavViewModel();

	UFUNCTION(BlueprintCallable)
	WIDGETAPPLICATION_API void SetNavViewModel(UGenericNavViewModel* InNavViewModel);

protected:
	UFUNCTION(BlueprintNativeEvent)
	WIDGETAPPLICATION_API void OnNavNumChanged(int32 InNum);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETAPPLICATION_API void OnNavIndexChanged(int32 InIndex);

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UGenericNavViewModel> NavViewModel = nullptr;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericButton> GenericButton_Left;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericButton> GenericButton_Right;
};
