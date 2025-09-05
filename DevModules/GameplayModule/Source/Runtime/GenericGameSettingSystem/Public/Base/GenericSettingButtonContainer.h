// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ButtonContainer/ButtonContainer_VerticalBox.h"
#include "GenericSettingButtonContainer.generated.h"

class UGenericButtonWidget;
class UPropertyList;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UGenericSettingButtonContainer : public UButtonContainer_VerticalBox
{
	GENERATED_BODY()

public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnButtonSelectionChanged(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton, bool InSelection);

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UPropertyList> PropertyList_Setting;
};
