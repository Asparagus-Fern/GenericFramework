// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyType.h"
#include "Object/CommonObject.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PropertyRegistry.generated.h"

class UPropertyEntity;

/**
 * 负责属性的注册反注册，属性变更的追踪
 */
UCLASS(Abstract)
class PROPERTYDETAILVIEWSYSTEM_API UPropertyRegistry : public UCommonObject
{
	GENERATED_BODY()

public:
	virtual void Initialize() PURE_VIRTUAL(,)

	/* 应用属性的修改 */
	virtual void ApplyPropertyChanges();

	/* 保存属性的修改 */
	virtual void SavePropertyChanges();

	/* 撤回属性的修改 */
	virtual void RestoreToInitial();

protected:
	void ClearDirtyState();

public:
	UFUNCTION(BlueprintCallable)
	void RegisterProperty(UPropertyEntity* InPropertyEntity);

	UFUNCTION(BlueprintCallable)
	void UnRegisterProperty(UPropertyEntity* InPropertyEntity);

private:
	void RegisterInnerProperty(UPropertyEntity* InPropertyEntity);
	void UnRegisterInnerProperty(UPropertyEntity* InPropertyEntity);
	
	void HandlePropertyChanged(UPropertyEntity* Property, EPropertyChangeReason Reason);
	void HandlePropertyApplied(UPropertyEntity* Property);
	void HandlePropertyEditConditionsChanged(UPropertyEntity* Property);

protected:
	virtual void OnPropertyChanged(UPropertyEntity* Property, EPropertyChangeReason Reason) { return; }
	virtual void OnPropertyApplied(UPropertyEntity* Property) { return; }
	virtual void OnPropertyEditConditionsChanged(UPropertyEntity* Property) { return; }

	/* 是否在修改时即刻保存属性值 */
	virtual bool GetIsAutoSaveProperty() { return true; }

public:
	DECLARE_EVENT_TwoParams(UPropertyRegistry, FOnPropertyChanged, UPropertyEntity*, EPropertyChangeReason);

	DECLARE_EVENT_OneParam(UPropertyRegistry, FOnPropertyApplied, UPropertyEntity*);

	DECLARE_EVENT_OneParam(UPropertyRegistry, FOnPropertyEditConditionsChanged, UPropertyEntity*);

	FOnPropertyChanged OnPropertyChangedEvent;
	FOnPropertyApplied OnPropertyAppliedEvent;
	FOnPropertyEditConditionsChanged OnPropertyEditConditionsChangedEvent;

protected:
	UPROPERTY(Transient)
	TArray<TObjectPtr<UPropertyEntity>> TopLevelProperties;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UPropertyEntity>> RegisteredProperties;

private:
	/* 表示属性发生了变化 */
	bool bPropertyChanged = false;

	/* 表示属性正在保存 */
	bool bRestoringProperty = false;

	/* 发生变更的属性 */
	TMap<FObjectKey, TWeakObjectPtr<UPropertyEntity>> DirtyProperties;
};
