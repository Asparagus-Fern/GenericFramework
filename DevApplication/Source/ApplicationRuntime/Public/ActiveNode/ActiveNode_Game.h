// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveNode.h"
#include "ActiveNode_Game.generated.h"

class UGameWidgetSetting;
class UGameWorldSetting;

UCLASS(HideCategories=(Object,Actor,Collision,Physics,Networking,Input,LevelInstance,Cooking,HLOD))
class APPLICATIONRUNTIME_API AActiveNode_Game : public AActiveNode
{
	GENERATED_BODY()

public:
	AActiveNode_Game();
	// virtual void BeginPlay() override;
	// virtual void Tick(float DeltaTime) override;

	/* AActiveNode */
public:
	virtual void LoginNode_Implementation() override;
	virtual void LogoutNode_Implementation() override;

public:
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Active Node Setting")
	// UGameWorldSetting* GameWorldSetting = nullptr;

protected:
	UFUNCTION()
	virtual void OnLoadCurrentWorldLevelStreamingFinish();

	UFUNCTION()
	virtual void OnSetProjectLevelsVisibleFinish();

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnFinish_LoadCurrentWorldLevelStreaming();

	UFUNCTION(BlueprintNativeEvent)
	void OnFinish_SetProjectLevelsVisible();
};
