// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DBTweenBase.h"
#include "UObject/Object.h"
#include "CommonButtonHandle.generated.h"

/**
 * 处理时间轴按钮事件的通用处理类
 */
UCLASS(Abstract, BlueprintType, EditInlineNew)
class SCREENWIDGETGENERATION_API UCommonButtonHandle : public UObject
{
	GENERATED_BODY()

public:
	/* 是否异步处理 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsAsync = false;

	/* 过渡时间 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Duration = 0.f;

	/* 过渡曲线类型 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EaseType EaseType = EaseType::Linear;

	/* 是否循环 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsLoop = false;

public:
	/* 更新处理 */
	virtual void UpdateHandle(FSimpleMulticastDelegate OnFinish = FSimpleMulticastDelegate());

	/* 当 Duration>0 时，将作为异步处理，将阻塞下一个异步处理 */
	virtual bool GetIsAsync();

protected:
	FSimpleMulticastDelegate OnHandleFinishDelegate;

	/* 当时间轴过渡时 */
	UFUNCTION()
	virtual void OnHandleUpdate(float InValue);

	/* 当时间轴完成时 */
	UFUNCTION()
	virtual void OnHandleFinish(float InValue);
};

/**
 * 处理材质参数集
 */
UCLASS(Abstract)
class UMaterialParameterHandle : public UCommonButtonHandle
{
	GENERATED_BODY()

public:
	/* 参数集 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialParameterCollection* Collection;

	/* 参数集名字 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ParameterName;
};

/**
 * 处理材质浮点参数
 */
UCLASS()
class UScalarParameterHandle : public UMaterialParameterHandle
{
	GENERATED_BODY()

public:
	/* 开始值 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StartValue = 0.f;

	/* 结束值 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float EndValue = 1.f;

public:
	virtual void UpdateHandle(FSimpleMulticastDelegate OnFinish) override;

protected:
	virtual void OnHandleUpdate(float InValue) override;
};

/**
 * 处理材质向量参数
 */
UCLASS()
class UVectorParameterHandle : public UMaterialParameterHandle
{
	GENERATED_BODY()

public:
	/* 开始值 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "bIsAsync"))
	FLinearColor StartValue;

	/* 结束值 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor EndValue;

public:
	virtual void UpdateHandle(FSimpleMulticastDelegate OnFinish) override;

protected:
	virtual void OnHandleUpdate(float InValue) override;
};
