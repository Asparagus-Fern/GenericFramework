// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSettingBool.h"
#include "GameSettingToggle.generated.h"

class USimpleTextBox;
/**
 * 
 */
UCLASS(Abstract)
class GAMESETTINGSYSTEM_API UGameSettingToggle : public UGameSettingBool
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void OnClicked_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DefaultText = FText::FromString("TextA");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ToggleText = FText::FromString("TextB");

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget = "SimpleTextBox"))
	USimpleTextBox* SimpleTextBox = nullptr;
};
