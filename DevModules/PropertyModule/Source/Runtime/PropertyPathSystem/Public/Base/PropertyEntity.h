// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyEditableState.h"
#include "PropertyEditCondition.h"
#include "PropertyType.h"
#include "Generic/GenericObject.h"
#include "PropertyEntity.generated.h"

class UPropertyRegistry;

/**
 * 属性
 */
UCLASS(Abstract)
class PROPERTYPATHSYSTEM_API UPropertyEntity : public UGenericObject
{
	GENERATED_BODY()

	/* ==================== UPropertyEntity ==================== */
public:
	void Initialize(UObject* InContext);
	void Apply();

protected:
	/* 开始初始化 */
	virtual void Startup();

	/* 初始化可能出现异步的情况 */
	void StartupComplete();

	/* 初始化完成时调用 */
	virtual void OnInitialized();

	/* 属性被应用时调用 */
	virtual void OnApply();

	/* 通知属性发生变更 */
	void NotifyPropertyChanged(EPropertyChangeReason Reason);

	/* 在属性发生变更时调用 */
	virtual void OnPropertyChanged(EPropertyChangeReason Reason);

public:
	UFUNCTION(BlueprintPure)
	bool IsContextValid() const;

	UFUNCTION(BlueprintPure)
	UObject* GetContext();

	UFUNCTION(BlueprintPure)
	UPropertyRegistry* GetOwnerRegistry();

	UFUNCTION(BlueprintCallable)
	void SetOwningRegistry(UPropertyRegistry* InOwningRegistry);

	UFUNCTION(BlueprintPure)
	UPropertyEntity* GetOwnerProperty() const;

	UFUNCTION(BlueprintCallable)
	void SetOwnerProperty(UPropertyEntity* InPropertyOwner);

	UFUNCTION(BlueprintPure)
	virtual TArray<UPropertyEntity*> GetChildProperties();

	UFUNCTION(BlueprintPure)
	FName GetPropertyName() const;

	UFUNCTION(BlueprintCallable)
	void SetPropertyName(FName InPropertyName);

	UFUNCTION(BlueprintPure)
	FText GetDisplayName() const;

	UFUNCTION(BlueprintCallable)
	void SetDisplayName(const FText& InDisplayName);

	UFUNCTION(BlueprintPure)
	FText GetDescriptionText() const;

	UFUNCTION(BlueprintCallable)
	void SetDescriptionText(const FText& InDescriptionText);

public:
	DECLARE_EVENT_TwoParams(UPropertyEntity, FOnPropertyChanged, UPropertyEntity*, EPropertyChangeReason);

	DECLARE_EVENT_OneParam(UPropertyEntity, FOnPropertyApplied, UPropertyEntity*);

	DECLARE_EVENT_OneParam(UPropertyEntity, FOnPropertyEditConditionChanged, UPropertyEntity*);

	FOnPropertyChanged OnPropertyChangedEvent;
	FOnPropertyEditConditionChanged OnPropertyEditConditionChangedEvent;
	FOnPropertyApplied OnPropertyAppliedEvent;
	
	/* ==================== Edit Dependency ==================== */
public:
	/* 添加属性的依赖，当依赖发生变更时，会刷新当前属性的状态 */
	void AddEditDependency(UPropertyEntity* DependencyPropertyEntity);

protected:
	void HandleEditDependencyChanged(UPropertyEntity* DependencyProperty, EPropertyChangeReason Reason);
	void HandleEditDependencyChanged(UPropertyEntity* DependencyProperty);

	/* 属性的依赖发生变更时调用 */
	virtual void OnDependencyChanged();

	/* ==================== Edit Condition ==================== */
public:
	/* 添加属性的编辑条件 */
	void AddEditCondition(const TSharedRef<FPropertyEditCondition>& InEditCondition);

protected:
	/* 通知属性编辑条件发生变更 */
	void NotifyEditConditionsChanged();

	/* 属性编辑条件发生变更时调用 */
	virtual void OnEditConditionsChanged();

private:
	bool bOnEditConditionsChangedEventGuard = false;

	/* ==================== Editable State ==================== */
public:
	const FPropertyEditableState& GetPropertyEditableState() const { return EditableStateCache; }

protected:
	/* 刷新编辑状态 */
	void RefreshEditableState(bool bNotifyEditConditionsChanged = true);

	/* 重新评估当前属性的编辑状态 */
	FPropertyEditableState ComputeEditableState() const;

	/* 属性重新评估编辑状态时调用 */
	virtual void OnGatherEditState(FPropertyEditableState& InOutEditState) const;

private:
	/* 编辑状态缓存，防止每次都重新评估 */
	FPropertyEditableState EditableStateCache;

	/* ==================== Property Entity ==================== */
protected:
	/* 属性的来源，查看 PropertyPathHelpers 的 FCachedPropertyPath 了解详细 */
	UPROPERTY(Transient)
	TObjectPtr<UObject> Context;

	/* 属性的Owner，用于支持属性的嵌套 */
	UPROPERTY(Transient)
	TObjectPtr<UPropertyEntity> OwnerProperty;

	UPROPERTY(Transient)
	TObjectPtr<UPropertyRegistry> OwningRegistry;

	UPROPERTY(EditAnywhere, Getter, BlueprintGetter="GetPropertyName", meta=(ExposeOnSpawn = true))
	FName PropertyName;

	UPROPERTY(EditAnywhere, Getter, BlueprintGetter="GetDisplayName", meta=(ExposeOnSpawn = true))
	FText DisplayName;

	UPROPERTY(EditAnywhere, Getter, BlueprintGetter="GetDescriptionText", meta=(ExposeOnSpawn = true))
	FText DescriptionText;

	/* 编辑条件 */
	TArray<TSharedRef<FPropertyEditCondition>> EditConditions;

private:
	/* 表示是否已经初始化 */
	bool bInitialize = false;

	/* 表示是否初始化完，防止多次初始化 */
	bool bReady = false;

	bool bOnPropertyChangedEventGuard = false;
};
