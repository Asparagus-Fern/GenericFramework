// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Manager/CoreManager.h"
#include "ActiveNodeManager.generated.h"

/**
 * 
 */
UCLASS()
class ACTIVENODESYSTEM_API UActiveNodeManager : public UCoreManager
{
	GENERATED_BODY()

public:
	UActiveNodeManager();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	static UActiveNodeManager* Get();

	/* UActiveNodeManager */
public:
	// 在世界即将开始时自动进入活跃点.
	UPROPERTY(Config, EditDefaultsOnly)
	uint8 bAutoLogin : 1;

	// 如果不支持更新, 将在活跃点管理子系统层面直接停用所有更新.
	UPROPERTY(Config, EditDefaultsOnly)
	uint8 bBlockUpdate : 1;

	/* 全局默认进入的活跃点Tag */
	UPROPERTY(Config, EditAnywhere, meta = (Categories = "ActiveNode"))
	FGameplayTag DefaultNodeTag;
};
