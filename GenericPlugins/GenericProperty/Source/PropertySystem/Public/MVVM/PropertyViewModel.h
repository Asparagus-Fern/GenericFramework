// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "PropertyType.h"
#include "PropertyViewModel.generated.h"

class UPropertyProxy;

static FName DefaultPropertyName = FName("GenerateChildProperty");

/**
 * 
 */
UCLASS(MinimalAPI, EditInlineNew)
class UPropertyViewModel : public UMVVMViewModelBase
{
	GENERATED_UCLASS_BODY()

public:
	DECLARE_EVENT_OneParam(UPropertyViewModel, FPropertyDelegate, UPropertyViewModel*)

	DECLARE_EVENT_TwoParams(UPropertyViewModel, FOnPropertyChanged, UPropertyViewModel*, EPropertyChangedReason)

	DECLARE_EVENT_TwoParams(UPropertyViewModel, FOnPropertyOptionTagChanged, UPropertyViewModel*, FGameplayTag)

	PROPERTYSYSTEM_API virtual bool Initialize(UPropertyProxy* InOwnerProxy);
	PROPERTYSYSTEM_API virtual void Deinitialize();

private:
	void HandleOnPropertyDependencyValueChanged(UPropertyViewModel* InPropertyViewModel, EPropertyChangedReason ChangedReason);

public:
	PROPERTYSYSTEM_API virtual void Startup();
	PROPERTYSYSTEM_API void StartupComplete();

	PROPERTYSYSTEM_API virtual void Apply();
	PROPERTYSYSTEM_API virtual void Reset();

	PROPERTYSYSTEM_API void PrePropertyChanged();
	PROPERTYSYSTEM_API void PostPropertyChanged();
	PROPERTYSYSTEM_API void NotifyPropertyChanged(EPropertyChangedReason ChangedReason);

protected:
	PROPERTYSYSTEM_API virtual bool CanApply();
	PROPERTYSYSTEM_API virtual bool CanReset();

public:
	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API UPropertyProxy* GetOwnerProxy() const;

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API bool GetIsInitialized() const;

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API bool GetIsReady() const;

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API bool GetIsPropertyValueDirty() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetIsEnableEdit(bool IsEnableEdit);
	
public:
	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API bool GetIsAutoApplyProperty() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetIsAutoApplyProperty(bool InIsAutoApplyProperty);

	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API bool GetIsDirtyProxy() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetIsDirtyProxy(bool InIsDirtyProxy);

	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API bool GetIsEditable() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetIsEditable(bool InIsEditable);

	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API bool GetIsVisible() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetIsVisible(bool InIsVisible);

	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API FName GetPropertyName() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetPropertyName(FName InPropertyName);

	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API const FText& GetPropertyDisplayName() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetPropertyDisplayName(const FText& InPropertyDisplayName);

	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API const FText& GetPropertyDescription() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetPropertyDescription(const FText& InPropertyDescription);

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void AddPropertyDependency(UPropertyViewModel* InPropertyDependency);

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void RemovePropertyDependency(UPropertyViewModel* InPropertyDependency);

	UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="Property"))
	PROPERTYSYSTEM_API void AddPropertyTag(FGameplayTag InPropertyTag);

	UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="Property"))
	PROPERTYSYSTEM_API void RemovePropertyTag(FGameplayTag InPropertyTag);

	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="Property"))
	PROPERTYSYSTEM_API bool HasPropertyTag(FGameplayTag InPropertyTag) const;

	PROPERTYSYSTEM_API FPropertyDelegate& GetOnPropertyReadyEvent() { return OnPropertyReadyEvent; }
	PROPERTYSYSTEM_API FPropertyDelegate& GetOnPropertyApplyEvent() { return OnPropertyApplyEvent; }
	PROPERTYSYSTEM_API FPropertyDelegate& GetOnPropertyResetEvent() { return OnPropertyResetEvent; }
	PROPERTYSYSTEM_API FPropertyDelegate& GetOnPropertyDependencyAddedEvent() { return OnPropertyDependencyAddedEvent; }
	PROPERTYSYSTEM_API FPropertyDelegate& GetOnPropertyDependencyRemovedEvent() { return OnPropertyDependencyRemovedEvent; }
	PROPERTYSYSTEM_API FOnPropertyOptionTagChanged& GetOnPropertyTagOptionAddedEvent() { return OnPropertyOptionTagAddedEvent; }
	PROPERTYSYSTEM_API FOnPropertyOptionTagChanged& GetOnPropertyTagOptionRemovedEvent() { return OnPropertyOptionTagRemovedEvent; }
	PROPERTYSYSTEM_API FOnPropertyChanged& GetOnPropertyChangedEvent() { return OnPropertyChangedEvent; }

protected:
	PROPERTYSYSTEM_API virtual void OnPropertyInitialized();
	PROPERTYSYSTEM_API virtual void OnPropertyDeinitialized();
	PROPERTYSYSTEM_API virtual void OnPropertyApply();
	PROPERTYSYSTEM_API virtual void OnPropertyReset();
	PROPERTYSYSTEM_API virtual void OnPropertyDependencyAdded(UPropertyViewModel* InPropertyDependency);
	PROPERTYSYSTEM_API virtual void OnPropertyDependencyRemoved(UPropertyViewModel* InPropertyDependency);
	PROPERTYSYSTEM_API virtual void OnPropertyDependencyValueChanged(UPropertyViewModel* InPropertyDependency, EPropertyChangedReason ChangedReason);
	PROPERTYSYSTEM_API virtual void OnPropertyTagAdded(FGameplayTag InPropertyTag);
	PROPERTYSYSTEM_API virtual void OnPropertyTagRemoved(FGameplayTag InPropertyTag);
	PROPERTYSYSTEM_API virtual void PrePropertyValueChanged();
	PROPERTYSYSTEM_API virtual void PostPropertyValueChanged();
	PROPERTYSYSTEM_API virtual void OnPropertyValueChanged(EPropertyChangedReason ChangedReason);

public:
	/* If True, When This Property Changed, Will Immediately Apply The Changed*/
	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetIsAutoApplyProperty", BlueprintSetter="SetIsAutoApplyProperty")
	bool IsAutoApplyProperty = false;

	/* If True, When This Property Changed, Will Update All Property In The Same Collection */
	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetIsDirtyProxy", BlueprintSetter="SetIsDirtyProxy")
	bool IsDirtyProxy = false;

	/* True If This Property Can Be Visible */
	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetIsVisible", BlueprintSetter="SetIsVisible")
	bool IsVisible = true;

	/* True If This Property Can Be Edit */
	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetIsEditable", BlueprintSetter="SetIsEditable")
	bool IsEditable = true;

	/* Help To Get This Property */
	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetPropertyName", BlueprintSetter="SetPropertyName")
	FName PropertyName = DefaultPropertyName;

	/* Display Name */
	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetPropertyDisplayName", BlueprintSetter="SetPropertyDisplayName")
	FText PropertyDisplayName;

	/* Description */
	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetPropertyDescription", BlueprintSetter="SetPropertyDescription")
	FText PropertyDescription;

	/* If Dependency Property Changed, Will Update Self */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UPropertyViewModel>> PropertyDependencyList;

	/* If Edit Condition Property Changed, Will Update Self Editable State */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UPropertyViewModel>> PropertyEditConditionList;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadOnly, meta=(Categories="Property"))
	TArray<FGameplayTag> PropertyOptionTags;

private:
	bool bIsInitialized = false;
	bool bIsReady = false;
	bool bIsPropertyDirty = false;
	bool bIsEnableEdit = true;

	UPROPERTY()
	TObjectPtr<UPropertyProxy> OwnerProxy = nullptr;

	FPropertyDelegate OnPropertyReadyEvent;
	FPropertyDelegate OnPropertyApplyEvent;
	FPropertyDelegate OnPropertyResetEvent;
	FPropertyDelegate OnPropertyDependencyAddedEvent;
	FPropertyDelegate OnPropertyDependencyRemovedEvent;
	FOnPropertyOptionTagChanged OnPropertyOptionTagAddedEvent;
	FOnPropertyOptionTagChanged OnPropertyOptionTagRemovedEvent;
	FOnPropertyChanged OnPropertyChangedEvent;
};
