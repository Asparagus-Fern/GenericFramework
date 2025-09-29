// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GenericButtonConfirm.h"
#include "GenericSettingConfirm.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericSettingConfirm : public UGenericButtonConfirm
{
	GENERATED_BODY()

protected:
	GENERICGAMESETTINGSYSTEM_API virtual void ConfirmButtonSelection(bool bInSelected) override;
};
