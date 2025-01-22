// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetDelegate.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "WidgetManager.generated.h"

class UUserWidgetBase;

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_PreWidgetOpened, UUserWidgetBase*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_PreWidgetOpened, UUserWidgetBase*, InWidget);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnWidgetOpened, UUserWidgetBase*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnWidgetOpened, UUserWidgetBase*, InWidget);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnWidgetClosed, UUserWidgetBase*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnWidgetClosed, UUserWidgetBase*, InWidget);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_PostWidgetClosed, UUserWidgetBase*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_PostWidgetClosed, UUserWidgetBase*, InWidget);

/**
 * 
 */
USTRUCT()
struct FReplaceWidgetHandle
{
	GENERATED_BODY()

public:
	FReplaceWidgetHandle();
	FReplaceWidgetHandle(FGameplayTag InSlotTag, UUserWidgetBase* InNewWidget, const FOnWidgetActiveStateChanged& OnFinish);

	bool operator==(const FReplaceWidgetHandle& Other) const { return SlotTag == Other.SlotTag; }
	bool operator==(const FGameplayTag Other) const { return SlotTag == Other; }

public:
	UPROPERTY()
	FGameplayTag SlotTag;

	UPROPERTY()
	UUserWidgetBase* NewWidget = nullptr;

	FOnWidgetActiveStateChanged OnFinishDelegate;
};

/**
 * 
 */
UCLASS()
class WIDGETGENERATION_API UWidgetManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

protected:
	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) override;
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override;

	/* Delegate From WidgetAnimationManager */
private:
	void OnWidgetAnimationPlayFinish(UUserWidgetBase* InWidget, bool InIsActive);

	/* UWidgetManager */
public:
	template <typename T>
	T* OpenUserWidget(TSubclassOf<UUserWidgetBase> InWidgetClass, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged())
	{
		if (UUserWidgetBase* NewWidget = OpenUserWidget(InWidgetClass, OnFinish))
		{
			return Cast<T>(NewWidget);
		}
		return nullptr;
	}

	virtual UUserWidgetBase* OpenUserWidget(TSubclassOf<UUserWidgetBase> InWidgetClass, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	virtual bool OpenUserWidget(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());

	virtual bool CloseUserWidget(FGameplayTag InSlotTag, bool MarkAsGarbage = true, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	virtual bool CloseUserWidget(UUserWidgetBase* InWidget, bool MarkAsGarbage = true, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());

	TArray<UUserWidgetBase*> GetActivedWidgets() { return ActivedWidgets; }

private:
	virtual void ActiveWidget(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	virtual void InactiveWidget(UUserWidgetBase* InWidget, bool MarkAsGarbage = true, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());

public:
	inline static FDelegate_PreWidgetOpened Delegate_PreWidgetOpened;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_PreWidgetOpened BPDelegate_PreWidgetOpened;

	inline static FDelegate_OnWidgetOpened Delegate_OnWidgetOpened;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnWidgetOpened BPDelegate_OnWidgetOpened;

	inline static FDelegate_OnWidgetClosed Delegate_OnWidgetClosed;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnWidgetClosed BPDelegate_OnWidgetClosed;

	inline static FDelegate_PostWidgetClosed Delegate_PostWidgetClosed;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_PostWidgetClosed BPDelegate_PostWidgetClosed;

protected:
	/* 当前显示在屏幕上的所有UI */
	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<TObjectPtr<UUserWidgetBase>> ActivedWidgets;

private:
	UPROPERTY(Transient)
	TArray<FReplaceWidgetHandle> ReplaceWidgetHandles;
};
