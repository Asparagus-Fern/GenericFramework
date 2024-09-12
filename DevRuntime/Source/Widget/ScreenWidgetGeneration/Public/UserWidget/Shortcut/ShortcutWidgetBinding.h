// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/PlayerInputBinding.h"
#include "ShortcutWidgetBinding.generated.h"

class UInputHandle;
class UUserWidgetBase;

USTRUCT(BlueprintType)
struct FShortcutWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	UUserWidgetBase* Widget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	UInputHandle* InputHandle;
};

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UShortcutWidgetBinding : public UPlayerInputBinding
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FShortcutWidget> ShortcutWidgets;

public:
	virtual void SetupBinding(UCommonInputComponent* CommonInputComponent) override;
	virtual void ClearupBinding(UCommonInputComponent* CommonInputComponent) override;
};
