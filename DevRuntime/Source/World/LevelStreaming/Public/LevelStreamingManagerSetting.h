// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ManagerSetting.h"
#include "LevelStreamingManagerSetting.generated.h"

/**
 * 
 */
UCLASS()
class LEVELSTREAMING_API ULevelStreamingManagerSetting : public UManagerSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	bool bAutoLoadWorldLevelStreaming = true;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UWorld>> VisibleLevels;
};
