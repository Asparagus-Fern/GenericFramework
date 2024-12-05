// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "InteractableWidgetGroupManager.generated.h"

class UInteractableUserWidgetBase;
class UCommonButtonGroup;

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
	DECLARE_EVENT_TwoParams(UScreenWidgetManager, FOnInteractableWidgetAdded, UInteractableUserWidgetBase*, FString);

	DECLARE_EVENT_TwoParams(UScreenWidgetManager, FOnInteractableWidgetRemoved, UInteractableUserWidgetBase*, FString);

	DECLARE_EVENT_OneParam(UScreenWidgetManager, FOnInteractableWidgetClearup, FString);

	/* 当一个InteractableWidget被添加进组时 */
	static FOnInteractableWidgetAdded OnInteractableWidgetAdded;

	/* 当一个InteractableWidget从组移除时 */
	static FOnInteractableWidgetRemoved OnInteractableWidgetRemoved;

	/* 当一个组被清除时 */
	static FOnInteractableWidgetClearup OnInteractableWidgetClearup;
	
	/* 添加一个InteractableWidget到组 */
	UFUNCTION(BlueprintCallable)
	void AddInteractableWidget(UInteractableUserWidgetBase* InteractableWidget, FString GroupName);

	/* 从组移除一个InteractableWidget */
	UFUNCTION(BlueprintCallable)
	void RemoveInteractableWidget(UInteractableUserWidgetBase* InteractableWidget, FString GroupName);

	/* 清除指定组 */
	UFUNCTION(BlueprintCallable)
	void ClearupInteractableWidgetGroup(const FString& GroupName, bool DeselectAll);

	/* 查询指定组 */
	UFUNCTION(BlueprintCallable)
	bool FindInteractableWidgetGroup(const FString& GroupName, UCommonButtonGroup*& Group) const;

public:
	TMap<FString, TObjectPtr<UCommonButtonGroup>> GetInteractableWidgetGroups() const { return InteractableWidgetGroups; }

protected:
	/* 当前管理的所有按钮组 */
	UPROPERTY(Transient)
	TMap<FString, TObjectPtr<UCommonButtonGroup>> InteractableWidgetGroups;
};
