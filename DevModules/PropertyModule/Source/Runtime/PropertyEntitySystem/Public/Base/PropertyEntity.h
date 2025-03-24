// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyType.h"
#include "Common/CommonObject.h"
#include "PropertyEntity.generated.h"

class UPropertyRegistry;
class UPropertyEditCondition;
class UPropertyEditableState;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UPropertyEntity : public UCommonObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	PROPERTYENTITYSYSTEM_API void Initialize(UObject* InSource, FName InPropertyName);

protected:
	virtual void Startup();
	void FinishStartup();
	virtual void OnInitialized();

	/* ==================== Description ==================== */
public:
	PROPERTYENTITYSYSTEM_API FName GetPropertyName() const;
	PROPERTYENTITYSYSTEM_API void SetPropertyName(FName InPropertyName);

	UFUNCTION(BlueprintPure)
	PROPERTYENTITYSYSTEM_API FText GetDisplayName() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYENTITYSYSTEM_API void SetDisplayName(const FText& InDisplayName);

	UFUNCTION(BlueprintPure)
	PROPERTYENTITYSYSTEM_API FText GetDescriptionText() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYENTITYSYSTEM_API void SetDescriptionText(const FText& InDescriptionText);

protected:
	UFUNCTION(BlueprintNativeEvent)
	FText GetDefaultDisplayName();

	UFUNCTION(BlueprintNativeEvent)
	FText GetDefaultDescriptionText();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn = true))
	FName PropertyName;

	UPROPERTY(EditAnywhere, meta=(ExposeOnSpawn = true), Getter, Setter, BlueprintGetter="GetDisplayName", BlueprintSetter="SetDisplayName")
	FText DisplayName;

	UPROPERTY(EditAnywhere, meta=(ExposeOnSpawn = true), Getter, Setter, BlueprintGetter="GetDescriptionText", BlueprintSetter="SetDescriptionText")
	FText DescriptionText;

	/* ==================== Edit Condition ==================== */
public:
	UFUNCTION(BlueprintCallable)
	PROPERTYENTITYSYSTEM_API void AddEditCondition(UPropertyEditCondition* InEditCondition);

	UFUNCTION(BlueprintCallable)
	PROPERTYENTITYSYSTEM_API void NotifyEditConditionsChanged();

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnEditConditionsChanged();

public:
	DECLARE_EVENT_OneParam(UPropertyEntity, FOnPropertyEditConditionChanged, UPropertyEntity*);

	FOnPropertyEditConditionChanged OnPropertyEditConditionChanged;

protected:
	UPROPERTY(EditAnywhere, Instanced)
	TArray<TObjectPtr<UPropertyEditCondition>> EditConditions;

private:
	bool bOnEditConditionsChangedEventGuard = false;

	/* ==================== Editable State ==================== */
public:
	UFUNCTION(BlueprintPure)
	PROPERTYENTITYSYSTEM_API UPropertyEditableState* GetEditableState();

	UFUNCTION(BlueprintCallable)
	PROPERTYENTITYSYSTEM_API void RefreshEditableState(bool bNotifyEditConditionsChanged = true);

protected:
	UFUNCTION(BlueprintCallable)
	void ComputeEditableState();

	UFUNCTION(BlueprintNativeEvent)
	void OnGatherEditState(UPropertyEditableState*& InOutEditState) const;

	UFUNCTION(BlueprintNativeEvent)
	void PostGatherEditState(UPropertyEditableState*& InOutEditState) const;

protected:
	UPROPERTY()
	TObjectPtr<UPropertyEditableState> EditableState = nullptr;

	/* ==================== Property Dependency ==================== */
public:
	PROPERTYENTITYSYSTEM_API void AddPropertyDependency(UPropertyEntity* DependencyProperty);

protected:
	void HandleDependencyPropertyChanged(UPropertyEntity* DependencySetting, EPropertyChangeReason Reason);
	void HandleDependencyPropertyEditConditionChanged(UPropertyEntity* DependencySetting);

	UFUNCTION(BlueprintNativeEvent)
	void OnDependencyPropertyChanged();

	/* ==================== UPropertyEntity ==================== */
public:
	UFUNCTION(BlueprintPure)
	PROPERTYENTITYSYSTEM_API bool IsSourceValid() const;

	UFUNCTION(BlueprintPure)
	PROPERTYENTITYSYSTEM_API UPropertyEntity* GetOwnerProperty() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYENTITYSYSTEM_API void SetOwnerProperty(UPropertyEntity* InOwnerProperty);

	UFUNCTION(BlueprintPure)
	PROPERTYENTITYSYSTEM_API UPropertyRegistry* GetOwningRegistry() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYENTITYSYSTEM_API void SetOwningRegistry(UPropertyRegistry* InOwnerRegistry);

	UFUNCTION(BlueprintCallable)
	PROPERTYENTITYSYSTEM_API void NotifyPropertyChanged(EPropertyChangeReason Reason);

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnPropertyChanged(EPropertyChangeReason Reason);

	UFUNCTION(BlueprintNativeEvent)
	void GetChildProperties(TArray<UPropertyEntity*>& Children);

public:
	DECLARE_EVENT_TwoParams(UPropertyEntity, FOnPropertyChanged, UPropertyEntity*, EPropertyChangeReason);

	DECLARE_EVENT_OneParam(UPropertyEntity, FOnPropertyApplied, UPropertyEntity*);

	FOnPropertyChanged OnPropertyChangedEvent;
	FOnPropertyApplied OnPropertyAppliedEvent;

protected:
	UPROPERTY(Transient)
	TObjectPtr<UObject> Source = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UPropertyEntity> OwnerProperty = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UPropertyRegistry> OwnerRegistry = nullptr;

private:
	bool bInitialize = false;
	bool bReady = false;
	bool bOnPropertyChangedEventGuard = false;
};
