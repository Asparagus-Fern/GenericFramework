// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget/Menu/MenuStyle.h"
#include "GameSettingMenu.generated.h"

class UGameSettingValueMapping;
class USimpleTextBox;
class UGameSettingValue;
class UTextBlock;

/**
 * 
 */
UCLASS()
class GAMESETTINGSYSTEM_API UGameSettingMenu : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetSettingName", BlueprintSetter="SetSettingName")
	FText SettingName = FText::FromString("SettingName");

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag Tag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UGameSettingValueMapping* GameSettingValueMapping = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly)
	USimpleTextBox* SimpleTextBox = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UGameSettingValue* GameSettingValue = nullptr;

public:
	UFUNCTION(BlueprintPure)
	FText GetSettingName() const;

	UFUNCTION(BlueprintCallable)
	void SetSettingName(FText InSettingName);
};
