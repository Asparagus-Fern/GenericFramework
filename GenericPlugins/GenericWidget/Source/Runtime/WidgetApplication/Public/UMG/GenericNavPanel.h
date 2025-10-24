// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "GenericNavPanel.generated.h"

class UGenericNavContent;
class UGenericNavBar;
class UGenericNavViewModel;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UGenericNavPanel : public UGenericWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	WIDGETAPPLICATION_API UGenericNavViewModel* GetNavViewModel();

	UFUNCTION(BlueprintCallable)
	WIDGETAPPLICATION_API void SetNavViewModel(UGenericNavViewModel* InNavViewModel);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TObjectPtr<UGenericNavViewModel> NavViewModel = nullptr;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericNavBar> NavBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericNavContent> NavContent;
};
