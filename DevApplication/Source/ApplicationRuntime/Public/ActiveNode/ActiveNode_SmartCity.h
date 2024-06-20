// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveNode_Game.h"
#include "ActiveNode_SmartCity.generated.h"

UCLASS()
class APPLICATIONRUNTIME_API AActiveNode_SmartCity : public AActiveNode_Game
{
	GENERATED_BODY()

public:
	AActiveNode_SmartCity();
	// virtual void BeginPlay() override;
	// virtual void Tick(float DeltaTime) override;

	/* AActiveNode */
public:
	virtual void LoginNode_Implementation() override;
	virtual void LogoutNode_Implementation() override;

	virtual void OnLoadCurrentWorldLevelStreamingFinish() override;
	virtual void OnSetProjectLevelsVisibleFinish() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Active Node Setting")
	UGameWidgetSetting* GameWidgetSetting = nullptr;
};
