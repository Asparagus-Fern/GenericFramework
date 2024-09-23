// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/GameSettingValue.h"
#include "GameSettingBool.generated.h"

class UButton;

/**
 * 
 */
UCLASS(Abstract)
class GAMESETTINGSYSTEM_API UGameSettingBool : public UGameSettingValue
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn = true))
	bool bStatus = false;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget = "Button"))
	UButton* Button = nullptr;

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnClicked();
};
