// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVM/Data/DataPropertyViewModel.h"
#include "MultiPropertyValueViewModel.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPropertyValueAdded, const FString&, UPropertyViewModel*);

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPropertyValueRemoved, const FString&, UPropertyViewModel*);

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UMultiPropertyValueViewModel : public UDataPropertyViewModel
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual bool Initialize(UPropertyProxy* InOwnerProxy) override;
	PROPERTYSYSTEM_API virtual void Deinitialize() override;

	PROPERTYSYSTEM_API virtual FString GetInitialValueAsString() override;
	PROPERTYSYSTEM_API virtual void SetInitialValueFromString(const FString& InValue) override;
	PROPERTYSYSTEM_API virtual FString GetCurrentValueAsString() override;
	PROPERTYSYSTEM_API virtual void SetCurrentValueFromString(const FString& InValue) override;

protected:
	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API virtual void AddValuesByName(const TMap<FString, FText>& InDisplayNames);

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void AddValues(const TMap<FString, UPropertyViewModel*>& InViewModels);

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void AddValueByName(FString InName, const FText& InDisplayName);

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void AddValue(FString InName, UPropertyViewModel* InViewModel);

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void RemoveValue(UPropertyViewModel* InViewModel);

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void RemoveValueByName(FString InName);

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void RemoveAllValues();

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API bool FindViewModel(const FString& InName, UPropertyViewModel*& OutViewModel) const;

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API bool FindViewModelName(UPropertyViewModel* InViewModel, FString& OutName) const;

public:
	UFUNCTION(BlueprintPure)
	int32 GetInitialValueIndex() const;

	UFUNCTION(BlueprintCallable)
	void SetInitialValueByIndex(int32 InIndex);

	UFUNCTION(FieldNotify, BlueprintPure)
	FString GetInitialValue() const;

	UFUNCTION(BlueprintCallable)
	void SetInitialValue(FString InValue);

	UFUNCTION(BlueprintPure)
	int32 GetSelectedValueIndex() const;

	UFUNCTION(BlueprintCallable)
	void SetSelectedValueByIndex(int32 InIndex);

	UFUNCTION(FieldNotify, BlueprintPure)
	FString GetSelectedValue() const;

	UFUNCTION(BlueprintCallable)
	void SetSelectedValue(FString InValue);

public:
	FOnPropertyValueAdded OnPropertyValueAddedEvent;
	FOnPropertyValueRemoved OnPropertyValueRemovedEvent;

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	bool bAllowWrap = false;

	UPROPERTY(FieldNotify, VisibleAnywhere, Getter, Setter, BlueprintGetter="GetInitialValue", BlueprintSetter="SetInitialValue")
	FString InitialValue;

	UPROPERTY(FieldNotify, VisibleAnywhere, Getter, Setter, BlueprintGetter="GetSelectedValue", BlueprintSetter="SetSelectedValue")
	FString SelectedValue;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadOnly, Instanced)
	TMap<FString, TObjectPtr<UPropertyViewModel>> PropertyValues;
};
