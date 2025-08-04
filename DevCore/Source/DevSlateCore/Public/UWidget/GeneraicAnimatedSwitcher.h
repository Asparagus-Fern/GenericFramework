// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonAnimatedSwitcher.h"
#include "GeneraicAnimatedSwitcher.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActiveIndexChangedFinish, UWidget*, ActiveWidget, int32, ActiveIndex);

/**
 * 
 */
UCLASS()
class DEVSLATECORE_API UGeneraicAnimatedSwitcher : public UCommonAnimatedSwitcher
{
	GENERATED_BODY()

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("GenericWidget", "Generic", "Generic Widget"); }
#endif

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnActiveIndexChangedFinish OnActiveIndexChangedFinish;

protected:
	virtual void HandleSlateActiveIndexChanged(int32 ActiveIndex) override;
};
