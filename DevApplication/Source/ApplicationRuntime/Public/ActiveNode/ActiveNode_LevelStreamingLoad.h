// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveNode_Load.h"
#include "ActiveNode_LevelStreamingLoad.generated.h"

class UUserWidgetBase;
class ULoading;

UCLASS(MinimalAPI)
class AActiveNode_LevelStreamingLoad : public AActiveNode_Load
{
	GENERATED_BODY()

public:
	AActiveNode_LevelStreamingLoad();

public:
	virtual void Login() override;
	virtual void Logout() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bLoadCurrentWorldLevels = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ULoading> LoadingClass = nullptr;

	UPROPERTY(VisibleAnywhere, Transient)
	ULoading* LoadingUI = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UWorld>> VisibleLevels;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnLoadCurrentWorldLevelStreamingOnceFinish();
	void NativeOnLoadCurrentWorldLevelStreamingOnceFinish();

	UFUNCTION(BlueprintNativeEvent)
	void OnLoadCurrentWorldLevelStreamingFinish();
	void NativeOnLoadCurrentWorldLevelStreamingFinish();

	UFUNCTION(BlueprintNativeEvent)
	void OnLoadVisibleLevelsOnceFinish();
	void NativeOnLoadVisibleLevelsOnceFinish();

	UFUNCTION(BlueprintNativeEvent)
	void OnLoadVisibleLevelsFinish();
	void NativeOnLoadVisibleLevelsFinish();

protected:
	int32 GetLoadingNum() const;
};
