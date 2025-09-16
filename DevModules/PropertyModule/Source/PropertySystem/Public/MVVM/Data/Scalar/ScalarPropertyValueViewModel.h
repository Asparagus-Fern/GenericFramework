// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVM/Data/DataPropertyViewModel.h"
#include "ScalarPropertyValueViewModel.generated.h"

UENUM(BlueprintType)
enum class EScalarPropertyValueDisplayFormat : uint8
{
	DisplayAsRawValue,
	DisplayAsNormalizedValue,
	DisplayAsCustom
};

/**
 * 
 */
UCLASS(MinimalAPI)
class UScalarPropertyValueViewModel : public UDataPropertyViewModel
{
	GENERATED_BODY()

public:
	virtual FString GetInitialValueAsString() override;
	virtual void SetInitialValueFromString(const FString& InValue) override;
	virtual FString GetCurrentValueAsString() override;
	virtual void SetCurrentValueFromString(const FString& InValue) override;

public:
	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API double GetInitialValue() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetInitialValue(double InValue);

	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API double GetNormalizedInitialValue() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetNormalizedInitialValue(double InValue);

	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API double GetCurrentValue() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetCurrentValue(double InValue);

	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API double GetNormalizedCurrentValue() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetNormalizedCurrentValue(double InValue);

	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API double GetValueStep() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetValueStep(double InValue);

	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API FVector2D GetValueRange() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetValueRange(FVector2D InValueRange);

	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API FVector2D GetNormalizedValueRange() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetNormalizedValueRange(FVector2D InValueRange);

	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API FVector2D GetValueInteractionRange() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetValueInteractionRange(FVector2D InValueRange);

	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API FVector2D GetNormalizedValueInteractionRange() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetNormalizedValueInteractionRange(FVector2D InValueRange);
	
protected:
	PROPERTYSYSTEM_API double NormalizeValue(double InValue) const;
	PROPERTYSYSTEM_API FVector2D NormalizeRange(FVector2D InValue) const;

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	EScalarPropertyValueDisplayFormat DisplayFormat = EScalarPropertyValueDisplayFormat::DisplayAsRawValue;

	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetInitialValue", BlueprintSetter="SetInitialValue")
	double InitialValue = 0.f;

	UPROPERTY(FieldNotify, Getter, Setter, BlueprintGetter="GetNormalizedInitialValue", BlueprintSetter="SetNormalizedInitialValue")
	double NormalizedInitialValue = 0.f;

	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetCurrentValue", BlueprintSetter="SetCurrentValue")
	double CurrentValue = 0.f;

	UPROPERTY(FieldNotify, Getter, Setter, BlueprintGetter="GetNormalizedCurrentValue", BlueprintSetter="SetNormalizedCurrentValue")
	double NormalizedCurrentValue = 0.f;

	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetValueStep", BlueprintSetter="SetValueStep")
	double ValueStep = 0.01f;

	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetValueRange", BlueprintSetter="SetValueRange")
	FVector2D ValueRange = FVector2D::ZeroVector;

	UPROPERTY(FieldNotify, Getter, Setter, BlueprintGetter="GetNormalizedValueRange", BlueprintSetter="SetNormalizedValueRange")
	FVector2D NormalizedValueRange = FVector2D::ZeroVector;

	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetValueInteractionRange", BlueprintSetter="SetValueInteractionRange")
	FVector2D ValueInteractionRange = FVector2D::ZeroVector;

	UPROPERTY(FieldNotify, Getter, Setter, BlueprintGetter="GetNormalizedValueInteractionRange", BlueprintSetter="SetNormalizedValueInteractionRange")
	FVector2D NormalizedValueInteractionRange = FVector2D::ZeroVector;
};
