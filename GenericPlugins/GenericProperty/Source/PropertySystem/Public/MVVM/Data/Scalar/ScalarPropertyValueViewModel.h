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
UCLASS()
class PROPERTYSYSTEM_API UScalarPropertyValueViewModel : public UDataPropertyViewModel
{
	GENERATED_BODY()

public:
	virtual FString GetInitialValueAsString() override;
	virtual void SetInitialValueFromString(const FString& InValue) override;
	virtual FString GetCurrentValueAsString() override;
	virtual void SetCurrentValueFromString(const FString& InValue) override;

public:
	UFUNCTION(FieldNotify, BlueprintPure)
	double GetInitialValue() const;

	UFUNCTION(BlueprintCallable)
	void SetInitialValue(double InValue);

	UFUNCTION(FieldNotify, BlueprintPure)
	double GetNormalizedInitialValue() const;

	UFUNCTION(BlueprintCallable)
	void SetNormalizedInitialValue(double InValue);

	UFUNCTION(FieldNotify, BlueprintPure)
	double GetCurrentValue() const;

	UFUNCTION(BlueprintCallable)
	void SetCurrentValue(double InValue);

	UFUNCTION(FieldNotify, BlueprintPure)
	double GetNormalizedCurrentValue() const;

	UFUNCTION(BlueprintCallable)
	void SetNormalizedCurrentValue(double InValue);

	UFUNCTION(FieldNotify, BlueprintPure)
	double GetValueStep() const;

	UFUNCTION(BlueprintCallable)
	void SetValueStep(double InValue);

	UFUNCTION(FieldNotify, BlueprintPure)
	bool GetIsClampValueRange() const;

	UFUNCTION(BlueprintCallable)
	void SetIsClampValueRange(bool InIsClampValueRange);

	UFUNCTION(FieldNotify, BlueprintPure)
	FVector2D GetValueRange() const;

	UFUNCTION(BlueprintCallable)
	void SetValueRange(FVector2D InValueRange);

	UFUNCTION(FieldNotify, BlueprintPure)
	FVector2D GetNormalizedValueRange() const;

	UFUNCTION(BlueprintCallable)
	void SetNormalizedValueRange(FVector2D InValueRange);

	UFUNCTION(FieldNotify, BlueprintPure)
	bool GetIsClampInteractionRange() const;

	UFUNCTION(BlueprintCallable)
	void SetIsClampInteractionRange(bool InIsClampInteractionRange);

	UFUNCTION(FieldNotify, BlueprintPure)
	FVector2D GetValueInteractionRange() const;

	UFUNCTION(BlueprintCallable)
	void SetValueInteractionRange(FVector2D InValueRange);

	UFUNCTION(FieldNotify, BlueprintPure)
	FVector2D GetNormalizedValueInteractionRange() const;

	UFUNCTION(BlueprintCallable)
	void SetNormalizedValueInteractionRange(FVector2D InValueRange);

protected:
	double NormalizeValue(double InValue) const;
	FVector2D NormalizeRange(FVector2D InValue) const;

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
	double ValueStep = 0.001f;

	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetIsClampValueRange", BlueprintSetter="SetIsClampValueRange")
	bool IsClampValueRange = false;

	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetValueRange", BlueprintSetter="SetValueRange")
	FVector2D ValueRange = FVector2D::ZeroVector;

	UPROPERTY(FieldNotify, Getter, Setter, BlueprintGetter="GetNormalizedValueRange", BlueprintSetter="SetNormalizedValueRange")
	FVector2D NormalizedValueRange = FVector2D::ZeroVector;

	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetIsClampInteractionRange", BlueprintSetter="SetIsClampInteractionRange")
	bool IsClampInteractionRange = false;

	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetValueInteractionRange", BlueprintSetter="SetValueInteractionRange")
	FVector2D ValueInteractionRange = FVector2D::ZeroVector;

	UPROPERTY(FieldNotify, Getter, Setter, BlueprintGetter="GetNormalizedValueInteractionRange", BlueprintSetter="SetNormalizedValueInteractionRange")
	FVector2D NormalizedValueInteractionRange = FVector2D::ZeroVector;
};
