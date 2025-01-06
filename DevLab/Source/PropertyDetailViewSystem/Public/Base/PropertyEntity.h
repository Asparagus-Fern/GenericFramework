// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyEditCondition.h"
#include "PropertyType.h"
#include "Common/CommonObject.h"
#include "PropertyEntity.generated.h"

class UPropertyRegistry;

/**
 * 属性
 */
UCLASS(Abstract)
class PROPERTYDETAILVIEWSYSTEM_API UPropertyEntity : public UCommonObject
{
	GENERATED_BODY()

public:
	void SetPropertyContext(UObject* InContext);
	void Initialize();
	void Initialize(UObject* InContext);
	void Apply();

public:
	/* 获取属性名 */
	UFUNCTION(BlueprintPure)
	FName GetPropertyName() const;
	void SetPropertyName(FName InPropertyName);

	/* 获取属性显示名 */
	UFUNCTION(BlueprintPure)
	FText GetDisplayName() const;
	void SetDisplayName(const FText& InDisplayName);

	/* 获取属性的描述 */
	UFUNCTION(BlueprintPure)
	FText GetDescriptionText() const;
	void SetDescriptionText(const FText& InDescriptionText);

public:
	bool IsContextValid() const { return (bool)Context; }
	virtual TArray<UPropertyEntity*> GetChildProperties() { return TArray<UPropertyEntity*>(); }

	void SetOwnerProperty(UPropertyEntity* InPropertyOwner);
	UPropertyEntity* GetOwnerProperty() const;

	void SetOwningRegistry(UPropertyRegistry* InOwningRegistry) { OwningRegistry = InOwningRegistry; }

	/* 添加属性的编辑条件 */
	void AddEditCondition(const TSharedRef<FPropertyEditCondition>& InEditCondition);

	/* 添加属性的依赖，当依赖发生变更时，会刷新当前属性的状态 */
	void AddEditDependency(UPropertyEntity* DependencyPropertyEntity);

	const FPropertyEditableState& GetPropertyEditableState() const { return EditableStateCache; }

protected:
	/* 开始初始化 */
	virtual void Startup();

	/* 初始化可能出现异步的情况 */
	void StartupComplete();

	/* 初始化完成时调用 */
	virtual void OnInitialized() { return; }

	/* 属性被应用时调用 */
	virtual void OnApply() { return; }

	/* 属性重新评估编辑状态时调用 */
	virtual void OnGatherEditState(FPropertyEditableState& InOutEditState) const { return; }

	/* 属性的依赖发生变更时调用 */
	virtual void OnDependencyChanged() { return; }

	void HandleEditDependencyChanged(UPropertyEntity* DependencySetting, EPropertyChangeReason Reason);
	void HandleEditDependencyChanged(UPropertyEntity* DependencySetting);

	/* 通知属性发生变更 */
	void NotifyPropertyChanged(EPropertyChangeReason Reason);

	/* 在属性发生变更时调用 */
	virtual void OnPropertyChanged(EPropertyChangeReason Reason) { return; }

	/* 通知属性编辑条件发生变更 */
	void NotifyEditConditionsChanged();

	/* 属性编辑条件发生变更时调用 */
	virtual void OnEditConditionsChanged() { return; }

	/* 重新评估当前属性的编辑状态 */
	FPropertyEditableState ComputeEditableState() const;

	/* 刷新编辑状态 */
	void RefreshEditableState(bool bNotifyEditConditionsChanged = true);

public:
	DECLARE_EVENT_TwoParams(UPropertyEntity, FOnPropertyChanged, UPropertyEntity*, EPropertyChangeReason);

	DECLARE_EVENT_OneParam(UPropertyEntity, FOnPropertyApplied, UPropertyEntity*);

	DECLARE_EVENT_OneParam(UPropertyEntity, FOnPropertyEditConditionChanged, UPropertyEntity*);

	FOnPropertyChanged OnPropertyChangedEvent;
	FOnPropertyApplied OnPropertyAppliedEvent;
	FOnPropertyEditConditionChanged OnPropertyEditConditionChangedEvent;

protected:
	/* 属性的来源，查看 PropertyPathHelpers 的 FCachedPropertyPath 了解详细 */
	UPROPERTY(Transient)
	TObjectPtr<UObject> Context;

	/* 属性的Owner，用于支持属性的嵌套 */
	UPROPERTY(Transient)
	TObjectPtr<UPropertyEntity> OwnerProperty;

	UPROPERTY(Transient)
	TObjectPtr<UPropertyRegistry> OwningRegistry;

	/* 唯一标识符 */
	UPROPERTY(EditAnywhere, Getter, BlueprintGetter="GetPropertyName", meta=(ExposeOnSpawn = true))
	FName PropertyName;

	/* 显示名 */
	UPROPERTY(EditAnywhere, Getter, BlueprintGetter="GetDisplayName", meta=(ExposeOnSpawn = true))
	FText DisplayName;

	/* 描述 */
	UPROPERTY(EditAnywhere, Getter, BlueprintGetter="GetDescriptionText", meta=(ExposeOnSpawn = true))
	FText DescriptionText;

	/* 编辑条件 */
	TArray<TSharedRef<FPropertyEditCondition>> EditConditions;

private:
	/* 表示是否已经初始化 */
	bool bInitialize = false;

	/* 表示是否初始化完，防止多次初始化 */
	bool bReady = false;

	/* 编辑状态缓存，防止每次都重新评估 */
	FPropertyEditableState EditableStateCache;

	bool bOnPropertyChangedEventGuard = false;
	bool bOnEditConditionsChangedEventGuard = false;
};
