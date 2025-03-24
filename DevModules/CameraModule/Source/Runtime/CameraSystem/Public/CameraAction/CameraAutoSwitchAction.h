// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputIdleAction/PlayerInputIdleAction.h"
#include "CameraAutoSwitchAction.generated.h"

class UCameraSwitchMethod;

/**
 * 
 */
UCLASS(MinimalAPI)
class UCameraAutoSwitchAction : public UPlayerInputIdleAction
{
	GENERATED_BODY()

public:
	UCameraAutoSwitchAction(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void HandleStartAction() override;
	virtual void HandleStopAction() override;

protected:
	void SwitchToNext();

public:
	/* If True, Start Timer When Camera Switch Finish. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsTimerAfrerSwitchFinsih = true;

	/* The Interval Idle Time When Switch Camera From A To B. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = 0, ClampMin = 0, Units = "s"))
	float TimeInterval = 10.f;

	/* Camera Switch Method */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UCameraSwitchMethod* CameraHandle = nullptr;

	/* Camera Tag Need To Switch */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Camera", EditCondition = "bEnableCameraAutoSwitch"))
	TArray<FGameplayTag> AutoSwitchTags;

private:
	int32 CurrentIndex = -1;
	FTimerHandle AutoSwitchCameraTimerHandle;
};
