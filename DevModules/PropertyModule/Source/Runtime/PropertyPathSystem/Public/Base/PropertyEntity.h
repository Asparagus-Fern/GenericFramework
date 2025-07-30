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
UCLASS(Abstract, MinimalAPI)
class UPropertyEntity : public UGenericObject
{
	GENERATED_BODY()

	/* ==================== UPropertyEntity ==================== */
public:
	PROPERTYPATHSYSTEM_API void Initialize(UObject* InContext);
	PROPERTYPATHSYSTEM_API void Apply();

protected:
	/* 开始初始化 */
	PROPERTYPATHSYSTEM_API virtual void Startup();

	/* 初始化可能出现异步的情况 */
	PROPERTYPATHSYSTEM_API void StartupComplete();

	/* 初始化完成时调用 */
	PROPERTYPATHSYSTEM_API virtual void OnInitialized();

	/* 属性被应用时调用 */
	PROPERTYPATHSYSTEM_API virtual void OnApply();

	/* 通知属性发生变更 */
	PROPERTYPATHSYSTEM_API void NotifyPropertyChanged(EPropertyChangeReason Reason);

	/* 在属性发生变更时调用 */
	PROPERTYPATHSYSTEM_API virtual void OnPropertyChanged(EPropertyChangeReason Reason);

public:
	UFUNCTION(BlueprintPure)
	PROPERTYPATHSYSTEM_API bool IsContextValid() const;

	UFUNCTION(BlueprintPure)
	PROPERTYPATHSYSTEM_API UObject* GetContext();

	UFUNCTION(BlueprintPure)
	PROPERTYPATHSYSTEM_API UPropertyRegistry* GetOwnerRegistry();

	UFUNCTION(BlueprintCallable)
	PROPERTYPATHSYSTEM_API void SetOwningRegistry(UPropertyRegistry* InOwningRegistry);

	UFUNCTION(BlueprintPure)
	PROPERTYPATHSYSTEM_API UPropertyEntity* GetOwnerProperty() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYPATHSYSTEM_API void SetOwnerProperty(UPropertyEntity* InPropertyOwner);

	UFUNCTION(BlueprintPure)
	PROPERTYPATHSYSTEM_API virtual TArray<UPropertyEntity*> GetChildProperties();

	UFUNCTION(BlueprintPure)
	PROPERTYPATHSYSTEM_API FName GetPropertyName() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYPATHSYSTEM_API void SetPropertyName(FName InPropertyName);

	UFUNCTION(BlueprintPure)
	PROPERTYPATHSYSTEM_API FText GetDisplayName() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYPATHSYSTEM_API void SetDisplayName(const FText& InDisplayName);

	UFUNCTION(BlueprintPure)
	PROPERTYPATHSYSTEM_API FText GetDescriptionText() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYPATHSYSTEM_API void SetDescriptionText(const FText& InDescriptionText);

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
	PROPERTYPATHSYSTEM_API void AddEditDependency(UPropertyEntity* DependencyPropertyEntity);

protected:
	void HandleEditDependencyChanged(UPropertyEntity* DependencyProperty, EPropertyChangeReason Reason);
	void HandleEditDependencyChanged(UPropertyEntity* DependencyProperty);

	/* 属性的依赖发生变更时调用 */
	PROPERTYPATHSYSTEM_API virtual void OnDependencyChanged();

	/* ==================== Edit Condition ==================== */
public:
	/* 添加属性的编辑条件 */
	PROPERTYPATHSYSTEM_API void AddEditCondition(const TSharedRef<FPropertyEditCondition>& InEditCondition);

protected:
	/* 通知属性编辑条件发生变更 */
	void NotifyEditConditionsChanged();

	/* 属性编辑条件发生变更时调用 */
	PROPERTYPATHSYSTEM_API virtual void OnEditConditionsChanged();

private:
	bool bOnEditConditionsChangedEventGuard = false;

	/* ==================== Editable State ==================== */
public:
	PROPERTYPATHSYSTEM_API const FPropertyEditableState& GetPropertyEditableState() const { return EditableStateCache; }

protected:
	/* 刷新编辑状态 */
	void RefreshEditableState(bool bNotifyEditConditionsChanged = true);

	/* 重新评估当前属性的编辑状态 */
	FPropertyEditableState ComputeEditableState() const;

	/* 属性重新评估编辑状态时调用 */
	PROPERTYPATHSYSTEM_API virtual void OnGatherEditState(FPropertyEditableState& InOutEditState) const;

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
