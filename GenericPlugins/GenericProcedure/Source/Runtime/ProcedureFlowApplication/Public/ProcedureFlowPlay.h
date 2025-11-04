// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureFlowExecute.h"
#include "ProcedureFlowPlay.generated.h"

class UGenericCameraSwitchMethod;

UCLASS(MinimalAPI)
class UProcedureFlowPlay : public UProcedureFlowExecute
{
	GENERATED_BODY()

protected:
	PROCEDUREFLOWAPPLICATION_API virtual void OnProcedureFlowEnter_Implementation() override;
	PROCEDUREFLOWAPPLICATION_API virtual void OnProcedureFlowExit_Implementation() override;

	/* Camera */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Camera"), Category="Camera")
	FGameplayTag DefaultCameraTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Camera")
	UGenericCameraSwitchMethod* CameraHandle = nullptr;
};
