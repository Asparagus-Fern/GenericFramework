// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "InteractableWidgetGroupManager.generated.h"

class UInteractableWidgetBase;
class UCommonButtonGroup;

DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate_OnInteractableWidgetAdded, UInteractableWidgetBase*, FString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBPDelegate_OnInteractableWidgetAdded, UInteractableWidgetBase*, InWidget, FString, InGroupName);

DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate_OnInteractableWidgetRemoved, UInteractableWidgetBase*, FString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBPDelegate_OnInteractableWidgetRemoved, UInteractableWidgetBase*, InWidget, FString, InGroupName);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnInteractableWidgetClearup, FString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnInteractableWidgetClearup, FString, InGroupName);

/**
 * 管理可交互UI的分组
 */
UCLASS()
class SCREENWIDGETGENERATION_API UInteractableWidgetGroupManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

public:
	/* 添加一个InteractableWidget到组 */
	UFUNCTION(BlueprintCallable)
	void AddInteractableWidget(UInteractableWidgetBase* InteractableWidget, FString GroupName);

	/* 从组移除一个InteractableWidget */
	UFUNCTION(BlueprintCallable)
	void RemoveInteractableWidget(UInteractableWidgetBase* InteractableWidget, FString GroupName);

	/* 清除指定组 */
	UFUNCTION(BlueprintCallable)
	void ClearupInteractableWidgetGroup(const FString& GroupName, bool DeselectAll);

	/* 查询指定组 */
	UFUNCTION(BlueprintCallable)
	bool FindInteractableWidgetGroup(const FString& GroupName, UCommonButtonGroup*& Group) const;

public:
	inline static FDelegate_OnInteractableWidgetAdded Delegate_OnInteractableWidgetAdded;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnInteractableWidgetAdded BPDelegate_OnInteractableWidgetAdded;

	inline static FDelegate_OnInteractableWidgetRemoved Delegate_OnInteractableWidgetRemoved;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnInteractableWidgetRemoved BPDelegate_OnInteractableWidgetRemoved;

	inline static FDelegate_OnInteractableWidgetClearup Delegate_OnInteractableWidgetClearup;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnInteractableWidgetClearup BPDelegate_OnInteractableWidgetClearup;

public:
	TMap<FString, TObjectPtr<UCommonButtonGroup>> GetInteractableWidgetGroups() const { return InteractableWidgetGroups; }

protected:
	/* 当前管理的所有按钮组 */
	UPROPERTY(Transient)
	TMap<FString, TObjectPtr<UCommonButtonGroup>> InteractableWidgetGroups;
};
