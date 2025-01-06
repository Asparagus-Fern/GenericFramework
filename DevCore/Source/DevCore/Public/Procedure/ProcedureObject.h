// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureInterface.h"
#include "Common/CommonObject.h"
#include "ProcedureObject.generated.h"

/**
 * 异步/同步流程处理的基类
 */
UCLASS(Abstract)
class DEVCORE_API UProcedureObject : public UCommonObject, public IProcedureInterface
{
	GENERATED_BODY()

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;
	virtual void NativeOnRefresh() override;
	
	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MarkAsActivedFinish();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MarkAsInactivedFinish();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsAsync = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsActived = false;

public:
	FSimpleDelegate NativeOnActivedFinish;
	FSimpleDelegate NativeOnInactivedFinish;
};
