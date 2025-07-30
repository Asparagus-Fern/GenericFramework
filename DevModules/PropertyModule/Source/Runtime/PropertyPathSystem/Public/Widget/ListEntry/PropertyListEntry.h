// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyListEntryBase.h"
#include "PropertyListEntry.generated.h"

/**
 * 
 */
UCLASS(Abstract, NotBlueprintable, meta=(DisableNativeTick), MinimalAPI)
class UPropertyListEntry : public UPropertyListEntryBase
{
	GENERATED_BODY()

protected:
	virtual void SetPropertyEntity(UPropertyEntity* InProperty) override;

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> Text_DisplayName;
};
