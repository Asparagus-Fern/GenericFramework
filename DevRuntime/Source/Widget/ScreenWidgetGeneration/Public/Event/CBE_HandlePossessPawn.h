// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonEvent.h"
#include "CBE_HandlePossessPawn.generated.h"

/**
 * 处理Pawn控制权切换
 */
UCLASS()
class SCREENWIDGETGENERATION_API UCBE_HandlePossessPawn : public UCommonButtonEvent
{
	GENERATED_BODY()

public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="OnActived")
	TSubclassOf<APawn> ActivePossessPawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="OnInactived")
	TSubclassOf<APawn> InactivePossessPawn;
};
