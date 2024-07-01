// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_HandleLevelStreaming.generated.h"

/**
 * 
 */
UCLASS()
class LEVELSTREAMING_API UCBE_HandleLevelStreaming : public UCommonButtonEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSoftObjectPtr<UWorld>> ActivateLevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSoftObjectPtr<UWorld>> InactivateLevels;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;
	virtual bool GetIsAsync() override { return true; }

public:
	UFUNCTION()
	void OnActivateLevelsFinish();

	UFUNCTION()
	void OnInactivateLevelsFinish();
};
