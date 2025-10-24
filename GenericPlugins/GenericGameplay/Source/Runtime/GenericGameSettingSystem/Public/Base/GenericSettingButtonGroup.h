// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GenericButtonGroup.h"
#include "GenericSettingButtonGroup.generated.h"

class UGenericPopupWidget;
class UPropertyProxy;
class UGameSettingProxy;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UGenericSettingButtonGroup : public UGenericButtonGroup
{
	GENERATED_BODY()

public:
	GENERICGAMESETTINGSYSTEM_API virtual void NativeOnCreate() override;
	GENERICGAMESETTINGSYSTEM_API virtual void NativeOnDestroy() override;

private:
	virtual void OnPropertyProxyRegister(FGameplayTag InProxyTag, UPropertyProxy* InProxy);
	virtual void OnPropertyProxyUnRegister(FGameplayTag InProxyTag, UPropertyProxy* InProxy);

protected:
	GENERICGAMESETTINGSYSTEM_API virtual bool HandleOnButtonSelectionConfirmed(UGenericButtonWidget* InButton, bool InSelection) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGenericPopupWidget> PopupWidgetClass = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<UGameSettingProxy>> GameSettingProxies;
};
