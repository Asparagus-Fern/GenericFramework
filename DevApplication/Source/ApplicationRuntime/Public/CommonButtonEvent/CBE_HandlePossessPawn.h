// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_HandlePossessPawn.generated.h"

/**
 * 处理Pawn控制权切换
 */
UCLASS()
class APPLICATIONRUNTIME_API UCBE_HandlePossessPawn : public UCommonButtonEvent
{
	GENERATED_BODY()

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Pawn"), Category="OnActived")
	TMap<int32, FGameplayTag> ActivePawnTags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Pawn"), Category="OnInactived")
	TMap<int32, FGameplayTag> InactivePawnTags;
};
