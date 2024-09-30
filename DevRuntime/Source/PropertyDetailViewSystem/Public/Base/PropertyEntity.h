// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyEditCondition.h"
#include "PropertyType.h"
#include "Object/CommonObject.h"
#include "PropertyEntity.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROPERTYDETAILVIEWSYSTEM_API UPropertyEntity : public UCommonObject
{
	GENERATED_BODY()

public:
	void Initialize(UObject* InContext);

public:
	UFUNCTION(BlueprintPure)
	FName GetPropertyName() const;
	void SetPropertyName(FName InPropertyName);

	UFUNCTION(BlueprintPure)
	FText GetDisplayName() const;
	void SetDisplayName(const FText& InDisplayName);

	UFUNCTION(BlueprintPure)
	FText GetDescriptionText() const;
	void SetDescriptionText(const FText& InDescriptionText);

public:
	virtual TArray<UPropertyEntity*> GetChildProperties() { return TArray<UPropertyEntity*>(); }

	void SetPropertyOwner(UPropertyEntity* InPropertyOwner);
	UPropertyEntity* GetPropertyOwner() const;

	void AddEditCondition(const TSharedRef<FPropertyEditCondition>& InEditCondition);
	void AddEditDependency(UPropertyEntity* DependencyPropertyEntity);

	const FPropertyEditableState& GetPropertyEditableState() const { return EditableStateCache; }

protected:
	virtual void Startup();
	void StartupComplete();

	virtual void OnInitialized() { return; }
	virtual void OnApply() { return; }
	virtual void OnGatherEditState(FPropertyEditableState& InOutEditState) const { return; }
	virtual void OnDependencyChanged() { return; }

	void HandleEditDependencyChanged(UPropertyEntity* DependencySetting, EPropertyChangeReason Reason);
	void HandleEditDependencyChanged(UPropertyEntity* DependencySetting);

	void NotifyPropertyChanged(EPropertyChangeReason Reason);
	virtual void OnPropertyChanged(EPropertyChangeReason Reason) { return; }

	void NotifyEditConditionsChanged();
	virtual void OnEditConditionsChanged() { return; }

	FPropertyEditableState ComputeEditableState() const;
	void RefreshEditableState(bool bNotifyEditConditionsChanged = true);

public:
	DECLARE_EVENT_TwoParams(UPropertyEntity, FOnPropertyChanged, UPropertyEntity*, EPropertyChangeReason);

	DECLARE_EVENT_OneParam(UPropertyEntity, FOnPropertyApplied, UPropertyEntity*);

	DECLARE_EVENT_OneParam(UPropertyEntity, FOnPropertyEditConditionChanged, UPropertyEntity*);

	FOnPropertyChanged OnPropertyChangedEvent;
	FOnPropertyApplied OnPropertyAppliedEvent;
	FOnPropertyEditConditionChanged OnPropertyEditConditionChangedEvent;

protected:
	UPROPERTY(Transient)
	TObjectPtr<UObject> Context;

	UPROPERTY(Transient)
	TObjectPtr<UPropertyEntity> PropertyOwner;

	/* 唯一标识符 */
	UPROPERTY(EditAnywhere, Getter, BlueprintGetter="GetPropertyName", meta=(ExposeOnSpawn = true))
	FName PropertyName;

	UPROPERTY(EditAnywhere, Getter, BlueprintGetter="GetDisplayName", meta=(ExposeOnSpawn = true))
	FText DisplayName;

	UPROPERTY(EditAnywhere, Getter, BlueprintGetter="GetDescriptionText", meta=(ExposeOnSpawn = true))
	FText DescriptionText;

	TArray<TSharedRef<FPropertyEditCondition>> EditConditions;

private:
	bool bReady = false;
	FPropertyEditableState EditableStateCache;

	bool bOnPropertyChangedEventGuard = false;
	bool bOnEditConditionsChangedEventGuard = false;
};
