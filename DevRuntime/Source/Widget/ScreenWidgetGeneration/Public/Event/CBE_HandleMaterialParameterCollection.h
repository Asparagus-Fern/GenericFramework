// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonEvent.h"
#include "CBE_HandleMaterialParameterCollection.generated.h"

UCLASS(BlueprintType, EditInlineNew)
class UMaterialParameterHandle : public UObject
{
	GENERATED_BODY()

public:
	virtual void UpdateParameter();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsAsync = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "bIsAsync"))
	float Duration = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialParameterCollection* Collection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ParameterName;

protected:
	UFUNCTION()
	virtual void AsyncUpdateParameter(float InValue);
};

UCLASS()
class UScalarParameterHandle : public UMaterialParameterHandle
{
	GENERATED_BODY()

public:
	virtual void UpdateParameter() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "bIsAsync"))
	float StartValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float EndValue = 1.f;

protected:
	virtual void AsyncUpdateParameter(float InValue) override;
};

UCLASS()
class UVectorParameterHandle : public UMaterialParameterHandle
{
	GENERATED_BODY()

public:
	virtual void UpdateParameter() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "bIsAsync"))
	FLinearColor StartValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor EndValue;

protected:
	virtual void AsyncUpdateParameter(float InValue) override;
};

/**
 * 处理材质参数集的变化
 */
UCLASS()
class SCREENWIDGETGENERATION_API UCBE_HandleMaterialParameterCollection : public UCommonButtonEvent
{
	GENERATED_BODY()

public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UScalarParameterHandle*> ActiveScalarParameterHandles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UVectorParameterHandle*> ActiveVectorParameterHandles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UScalarParameterHandle*> InactiveScalarParameterHandles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UVectorParameterHandle*> InactiveVectorParameterHandles;
};
