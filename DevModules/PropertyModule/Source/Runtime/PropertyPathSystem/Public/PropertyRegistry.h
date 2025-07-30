// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyType.h"
#include "Generic/GenericObject.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PropertyRegistry.generated.h"

class UPropertyEntity;

/**
 * 负责属性的注册反注册，属性变更的追踪
 */
UCLASS(Abstract, MinimalAPI)
class UPropertyRegistry : public UGenericObject
{
	GENERATED_BODY()

public:
	PROPERTYPATHSYSTEM_API virtual void Initialize() PURE_VIRTUAL(,)

	/* 应用属性的修改 */
	PROPERTYPATHSYSTEM_API virtual void ApplyPropertyChanges();

	/* 保存属性的修改 */
	PROPERTYPATHSYSTEM_API virtual void SavePropertyChanges();

	/* 撤回属性的修改 */
	PROPERTYPATHSYSTEM_API virtual void RestoreToInitial();

protected:
	PROPERTYPATHSYSTEM_API void ClearDirtyState();

public:
	UFUNCTION(BlueprintCallable)
	PROPERTYPATHSYSTEM_API void RegisterProperty(UPropertyEntity* InPropertyEntity);

	UFUNCTION(BlueprintCallable)
	PROPERTYPATHSYSTEM_API void UnRegisterProperty(UPropertyEntity* InPropertyEntity);

private:
	void RegisterInnerProperty(UPropertyEntity* InPropertyEntity);
	void UnRegisterInnerProperty(UPropertyEntity* InPropertyEntity);

	void HandlePropertyChanged(UPropertyEntity* Property, EPropertyChangeReason Reason);
	void HandlePropertyApplied(UPropertyEntity* Property);
	void HandlePropertyEditConditionsChanged(UPropertyEntity* Property);

protected:
	PROPERTYPATHSYSTEM_API virtual void OnPropertyChanged(UPropertyEntity* Property, EPropertyChangeReason Reason) { return; }
	PROPERTYPATHSYSTEM_API virtual void OnPropertyApplied(UPropertyEntity* Property) { return; }
	PROPERTYPATHSYSTEM_API virtual void OnPropertyEditConditionsChanged(UPropertyEntity* Property) { return; }

	/* 是否在修改时即刻保存属性值 */
	PROPERTYPATHSYSTEM_API virtual bool GetIsAutoSaveProperty() { return true; }

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
