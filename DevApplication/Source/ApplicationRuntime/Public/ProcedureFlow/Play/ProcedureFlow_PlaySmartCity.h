// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureFlow_Play.h"
#include "ProcedureFlow_PlaySmartCity.generated.h"

class ACameraPointBase;
class UCameraHandle;
class UUserWidgetBase;
class UGameMenuSetting;

UCLASS()
class APPLICATIONRUNTIME_API AProcedureFlow_PlaySmartCity : public AProcedureFlow_Play
{
	GENERATED_BODY()

public:
	AProcedureFlow_PlaySmartCity();

protected:
	virtual void OnProcedureFlowEnter_Implementation() override;
	virtual void OnProcedureFlowExit_Implementation() override;

	/* UI */
public:
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	// UGameMenuSetting* DefaultGameMenu = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TArray<TSubclassOf<UUserWidgetBase>> DefaultOpenWidgetClasses;

	/* Camera */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Camera"), Category="Camera")
	FGameplayTag DefaultCameraTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Camera")
	UCameraHandle* CameraHandle = nullptr;

protected:
	UPROPERTY(Transient)
	TArray<UUserWidgetBase*> DefaultOpenWidgets;

protected:
	virtual void PostHUDCreated();
	virtual void OnCameraPointRegister(ACameraPointBase* InCameraPoint);
};
