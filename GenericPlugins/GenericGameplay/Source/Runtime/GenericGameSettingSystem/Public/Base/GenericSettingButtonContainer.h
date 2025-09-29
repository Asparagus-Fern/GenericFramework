// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UMG/ButtonContainer/ButtonContainer_VerticalBox.h"
#include "GenericSettingButtonContainer.generated.h"

class UPropertyCollection;
class UGenericButtonWidget;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UGenericSettingButtonContainer : public UButtonContainer_VerticalBox
{
	GENERATED_BODY()

public:
	GENERICGAMESETTINGSYSTEM_API virtual void NativeOnActived() override;
	GENERICGAMESETTINGSYSTEM_API virtual void NativeOnInactived() override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	GENERICGAMESETTINGSYSTEM_API void OnButtonSelectionChanged(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton, bool InSelection);

	UFUNCTION()
	GENERICGAMESETTINGSYSTEM_API virtual void OnApplyButtonClicked(UGenericButtonWidget* InButton);

	UFUNCTION()
	GENERICGAMESETTINGSYSTEM_API virtual void OnResetButtonClicked(UGenericButtonWidget* InButton);

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UPropertyCollection> PropertyCollection_Setting;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericButtonWidget> Button_Apply;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericButtonWidget> Button_Reset;
};
