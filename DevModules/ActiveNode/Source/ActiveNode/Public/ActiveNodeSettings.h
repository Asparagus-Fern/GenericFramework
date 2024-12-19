// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "ActiveNodeSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig)
class ACTIVENODE_API UActiveNodeSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()
public:
	virtual FName GetContainerName() const override
	{
		return TEXT("Project");
	}

	static const ThisClass* Get()
	{
		return GetDefault<ThisClass>();
	}

	UFUNCTION(BlueprintPure)
	static const UActiveNodeSettings* GetActiveNodeSettings() { return Get();}

	// 在世界即将开始时自动进入活跃点.
	UPROPERTY(Config, EditDefaultsOnly, Category = ActiveNodeSystem)
	uint8 bAutoLogin : 1;

	// 如果不支持更新, 将在活跃点管理子系统层面直接停用所有更新.
	UPROPERTY(Config, EditDefaultsOnly, Category = ActiveNodeSystem)
	uint8 bBlockUpdate : 1;
	
	/* 全局默认进入的活跃点Tag */
	UPROPERTY(Config, EditAnywhere, meta = (Categories = "ActiveNode"), Category = ActiveNodeSystem)
	FGameplayTag DefaultNodeTag;
};