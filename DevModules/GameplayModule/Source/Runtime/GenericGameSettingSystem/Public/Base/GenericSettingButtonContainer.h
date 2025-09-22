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
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnButtonSelectionChanged(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton, bool InSelection);

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UPropertyCollection> PropertyCollection_Setting;
};
