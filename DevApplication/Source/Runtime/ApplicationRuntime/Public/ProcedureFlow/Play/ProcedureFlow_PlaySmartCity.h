// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureFlow_Play.h"
#include "ProcedureFlow_PlaySmartCity.generated.h"

class ACameraPointBase;
class UCameraSwitchMethod;
class UGenericWidget;
class UGameMenuSetting;

UCLASS(MinimalAPI)
class AProcedureFlow_PlaySmartCity : public AProcedureFlow_Play
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
	TArray<TSubclassOf<UGenericWidget>> DefaultOpenWidgetClasses;

	/* Camera */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Camera"), Category="Camera")
	FGameplayTag DefaultCameraTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Camera")
	UCameraSwitchMethod* CameraHandle = nullptr;

protected:
	UPROPERTY(Transient)
	TArray<UGenericWidget*> DefaultOpenWidgets;

protected:
	virtual void PostHUDCreated();
	virtual void OnCameraPointRegister(ACameraPointBase* InCameraPoint);
};
