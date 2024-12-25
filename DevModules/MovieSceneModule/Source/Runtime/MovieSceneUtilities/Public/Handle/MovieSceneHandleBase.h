// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneInterface.h"
#include "Handle/HandleBase.h"

#include "MovieSceneHandleBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MOVIESCENEUTILITIES_API UMovieSceneHandleBase : public UHandleBase, public IMovieSceneInterface, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual TStatId GetStatId() const override { return UObject::GetStatID(); }
	virtual bool IsAllowedToTick() const override { return true; }
	virtual bool IsTickable() const override { return true; }
	virtual void Tick(float DeltaTime) override;

	/* FMovieSceneInterface */
public:
	virtual void OpenMovieScene_Implementation() override;
	virtual void CloseMovieScene_Implementation() override;

	virtual void SetMovieSceneSetting_Implementation(FMovieSceneSetting InMovieSceneSetting) override;

	virtual void RefreshMovieScenePanel_Implementation(EMovieSceneState InMovieSceneState, TSubclassOf<UMovieScenePanel> InMovieScenePanelClass) override;
	virtual void OpenMovieScenePanel(TSubclassOf<UMovieScenePanel> InMovieScenePanel) override;
	virtual void CloseMovieScenePanel() override;

	virtual void SetMovieSceneState_Implementation(EMovieSceneState InMovieSceneState) override;

	virtual void OnMovieSceneOpenFinish_Implementation() override;
	virtual void OnMovieScenePlayFinish_Implementation() override;
	virtual void OnMovieSceneSeekFinish_Implementation() override;
	virtual void OnMovieSceneCloseFinish_Implementation() override;

	/* UMovieSceneHandleBase */
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	FTimespan GetMovieSceneCurrentTime();

public:
	DECLARE_MULTICAST_DELEGATE(FMovieSceneDelegate)

	FMovieSceneDelegate OnOpenFinish;
	FMovieSceneDelegate OnPlayFinish;
	FMovieSceneDelegate OnSeekFinish;
	FMovieSceneDelegate OnCloseFinish;
	
private:
	uint8 bEnableLoopFragmentSeek : 1;
	uint8 bIsSeeking : 1;
	int32 PlayNum = 0;
	FTimerHandle LoopFragmentHandle;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Transient)
	UMovieScenePanel* MovieScenePanel = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Transient)
	FMovieSceneSetting MovieSceneSetting;
};
