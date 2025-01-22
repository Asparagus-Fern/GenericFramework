// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetDelegate.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "WidgetAnimationManager.generated.h"

class UUserWidgetBase;

DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate_OnWidgetAnimationPlayFinish, UUserWidgetBase*, bool);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBPDelegate_OnWidgetAnimationPlayFinish, UUserWidgetBase*, InHUD, bool, InActiveState);

/**
 * 处理UMG的动画过渡
 */
USTRUCT()
struct FWidgetAnimationTimerHandle
{
	GENERATED_BODY()

public:
	FWidgetAnimationTimerHandle();
	FWidgetAnimationTimerHandle(UUserWidgetBase* InWidget, bool InIsActive, FTimerHandle InTimerHandle);

	bool operator==(const FWidgetAnimationTimerHandle& Other) const;
	bool operator==(const UUserWidgetBase* Other) const;

public:
	UPROPERTY()
	UUserWidgetBase* Widget = nullptr;

	UPROPERTY()
	bool bIsActive = false;

	UPROPERTY()
	FTimerHandle TimerHandle;
};

/**
 * 
 */
UCLASS(MinimalAPI)
class UWidgetAnimationManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* Delegate From WidgetManager */
private:
	void OnWidgetOpened(UUserWidgetBase* InWidget);
	void OnWidgetClosed(UUserWidgetBase* InWidget);

	/* UWidgetAnimationManager */
public:
	bool PlayWidgetAnimation(UUserWidgetBase* InWidget, bool InIsActive, const FTimerDelegate& InDelegate = FTimerDelegate());

public:
	inline static FDelegate_OnWidgetAnimationPlayFinish Delegate_OnWidgetAnimationPlayFinish;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnWidgetAnimationPlayFinish BPDelegate_OnWidgetAnimationPlayFinish;

private:
	UPROPERTY(Transient)
	TArray<FWidgetAnimationTimerHandle> WidgetAnimationTimerHandles;

	void OnActiveAnimationPlayFinish(UUserWidgetBase* InWidget);
	void OnInactiveAnimationPlayFinish(UUserWidgetBase* InWidget);
};
