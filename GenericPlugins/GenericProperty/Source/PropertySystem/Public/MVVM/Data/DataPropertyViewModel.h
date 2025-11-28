// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MVVM/PropertyViewModel.h"
#include "DataPropertyViewModel.generated.h"

class UPropertyDataSource;

/**
 * Data Type Property
 */
UCLASS(Abstract, MinimalAPI)
class UDataPropertyViewModel : public UPropertyViewModel
{
	GENERATED_UCLASS_BODY()

protected:
	PROPERTYSYSTEM_API virtual bool Initialize(UPropertyProxy* InOwnerProxy) override;
	PROPERTYSYSTEM_API virtual void Deinitialize() override;

	PROPERTYSYSTEM_API virtual void OnPropertyApply() override;
	PROPERTYSYSTEM_API virtual void OnPropertyReset() override;
	PROPERTYSYSTEM_API virtual void OnPropertyDependencyValueChanged(UPropertyViewModel* InDependencyProperty, EPropertyChangedReason ChangedReason) override;
	PROPERTYSYSTEM_API virtual void OnPropertyValueChanged(EPropertyChangedReason ChangedReason) override;

public:
	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API FString GetPropertyGetterPath() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetPropertyGetterPath(const FString& InPropertyGetterPath);

	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API FString GetPropertySetterPath() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetPropertySetterPath(const FString& InPropertySetterPath);

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API UPropertyDataSource* GetPropertyDataSource();

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API bool SetPropertyDataSource(UPropertyDataSource* InPropertyDataSource);

public:
	PROPERTYSYSTEM_API virtual FString GetInitialValueAsString() PURE_VIRTUAL(, return TEXT("");)
	PROPERTYSYSTEM_API virtual void SetInitialValueFromString(const FString& InValue) PURE_VIRTUAL(,)
	PROPERTYSYSTEM_API virtual FString GetCurrentValueAsString() PURE_VIRTUAL(, return TEXT("");)
	PROPERTYSYSTEM_API virtual void SetCurrentValueFromString(const FString& InValue) PURE_VIRTUAL(,)

protected:
	/*
	 * Property Path To Get Property Value, Container Is Self
	 * Ex: GetOwnerProxy.GetPropertyVisualData
	 * The Property Must Have UPROPERTY Macro
	 */
	UPROPERTY(FieldNotify, VisibleAnywhere, Getter, Setter, BlueprintGetter="GetPropertyGetterPath", BlueprintSetter="SetPropertyGetterPath")
	FString PropertyGetterPath;

	/*
	 * Property Path To Set Property Value, Container Is Self
	 * Ex: GetOwnerProxy.SetPropertyVisualData
	 * The Property Must Have UPROPERTY Macro
	 */
	UPROPERTY(FieldNotify, VisibleAnywhere, Getter, Setter, BlueprintGetter="GetPropertySetterPath", BlueprintSetter="SetPropertySetterPath")
	FString PropertySetterPath;

private:
	UPROPERTY()
	TObjectPtr<UPropertyDataSource> PropertyDataSource = nullptr;
};
