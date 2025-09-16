// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "PropertyType.h"
#include "DataSource/PropertyDataSource.h"
#include "PropertyViewModel.generated.h"

class UPropertyProxy;

/**
 * 
 */
UCLASS(MinimalAPI)
class UPropertyViewModel : public UMVVMViewModelBase
{
	GENERATED_UCLASS_BODY()

public:
	DECLARE_EVENT_OneParam(UPropertyViewModel, FPropertyDelegate, UPropertyViewModel*)

	DECLARE_EVENT_TwoParams(UPropertyViewModel, FOnPropertyChanged, UPropertyViewModel*, EPropertyChangedReason)

	DECLARE_EVENT_OneParam(UPropertyViewModel, FOnPropertyDependencyChanged, UPropertyViewModel*)

	PROPERTYSYSTEM_API bool Initialize(UPropertyProxy* InOwnerProxy);
	PROPERTYSYSTEM_API void Deinitialize();

private:
	void HandleOnPropertyDependencyValueChanged(UPropertyViewModel* InPropertyViewModel, EPropertyChangedReason ChangedReason);

public:
	PROPERTYSYSTEM_API virtual void Apply();
	PROPERTYSYSTEM_API virtual void Reverse();
	PROPERTYSYSTEM_API virtual void Reset();
	PROPERTYSYSTEM_API void NotifyPropertyChanged(EPropertyChangedReason ChangedReason);

protected:
	PROPERTYSYSTEM_API virtual bool CanApply();
	PROPERTYSYSTEM_API virtual bool CanReverse();
	PROPERTYSYSTEM_API virtual bool CanReset();

public:
	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API UPropertyProxy* GetOwnerProxy() const;

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API bool GetIsPropertyValueDirty() const;

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

	PROPERTYSYSTEM_API FPropertyDelegate& GetOnPropertyApplyEvent() { return OnPropertyApplyEvent; }
	PROPERTYSYSTEM_API FPropertyDelegate& GetOnPropertyReverseEvent() { return OnPropertyReverseEvent; }
	PROPERTYSYSTEM_API FPropertyDelegate& GetOnPropertyResetEvent() { return OnPropertyResetEvent; }
	PROPERTYSYSTEM_API FOnPropertyChanged& GetOnPropertyChangedEvent() { return OnPropertyChangedEvent; }
	PROPERTYSYSTEM_API FOnPropertyDependencyChanged& GetOnPropertyDependencyAddedEvent() { return OnPropertyDependencyAddedEvent; }
	PROPERTYSYSTEM_API FOnPropertyDependencyChanged& GetOnPropertyDependencyRemovedEvent() { return OnPropertyDependencyRemovedEvent; }

protected:
	PROPERTYSYSTEM_API virtual bool OnPropertyInitialized();
	PROPERTYSYSTEM_API virtual void OnPropertyDeinitialized();
	PROPERTYSYSTEM_API virtual void OnPropertyApply();
	PROPERTYSYSTEM_API virtual void OnPropertyReverse();
	PROPERTYSYSTEM_API virtual void OnPropertyReset();
	PROPERTYSYSTEM_API virtual void OnPropertyDependencyAdded(UPropertyViewModel* InPropertyDependency);
	PROPERTYSYSTEM_API virtual void OnPropertyDependencyRemoved(UPropertyViewModel* InPropertyDependency);
	PROPERTYSYSTEM_API virtual void OnPropertyDependencyValueChanged(UPropertyViewModel* InDependencyProperty, EPropertyChangedReason ChangedReason);
	PROPERTYSYSTEM_API virtual void OnPropertyValueChanged(EPropertyChangedReason ChangedReason);

public:
	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetIsAutoApplyProperty", BlueprintSetter="SetIsAutoApplyProperty")
	bool IsAutoApplyProperty = false;

	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetIsDirtyProxy", BlueprintSetter="SetIsDirtyProxy")
	bool IsDirtyProxy = false;

	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetPropertyName", BlueprintSetter="SetPropertyName")
	FName PropertyName = NAME_None;

	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetPropertyDisplayName", BlueprintSetter="SetPropertyDisplayName")
	FText PropertyDisplayName;

	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetPropertyDescription", BlueprintSetter="SetPropertyDescription")
	FText PropertyDescription;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<TObjectPtr<UPropertyViewModel>> PropertyDependencyList;

private:
	bool bIsInitialized = false;
	bool bIsPropertyDirty = false;
	bool bOnPropertyChangedEventGuard = false;

	UPROPERTY()
	TObjectPtr<UPropertyProxy> OwnerProxy = nullptr;

	FPropertyDelegate OnPropertyApplyEvent;
	FPropertyDelegate OnPropertyReverseEvent;
	FPropertyDelegate OnPropertyResetEvent;
	FOnPropertyChanged OnPropertyChangedEvent;
	FOnPropertyDependencyChanged OnPropertyDependencyAddedEvent;
	FOnPropertyDependencyChanged OnPropertyDependencyRemovedEvent;
};
