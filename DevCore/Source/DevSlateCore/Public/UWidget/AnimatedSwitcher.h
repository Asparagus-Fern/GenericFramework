// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonAnimatedSwitcher.h"
#include "AnimatedSwitcher.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActiveIndexChangedFinish, UWidget*, ActiveWidget, int32, ActiveIndex);

/**
 * 
 */
UCLASS()
class DEVSLATECORE_API UAnimatedSwitcher : public UCommonAnimatedSwitcher
{
	GENERATED_BODY()

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "Common", "Dev Widget"); }
#endif

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnActiveIndexChangedFinish OnActiveIndexChangedFinish;

protected:
	virtual void HandleSlateActiveIndexChanged(int32 ActiveIndex) override;
};
