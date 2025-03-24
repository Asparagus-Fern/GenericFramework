// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "PawnSpringArmComponent.generated.h"

/**
 * 提供SpringArm的平滑过渡
 */
UCLASS(ClassGroup=(Developer), meta=(BlueprintSpawnableComponent), MinimalAPI)
class UPawnSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

public:
	UPawnSpringArmComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpringArmLag = 5.f;

	UPROPERTY()
	bool bEnableReassessmentFocus = true;

	/* When Spring Arm Length Smaller Than ReassessmentFocus, Will Gather New Spring Arm Length. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = bEnableReassessmentSpringArmLength))
	float ReassessmentFocus = 10000.f;

	/* When Spring Arm Length Bigger Than ReassessmentFocus + ReassessmentFocusRange, Will Enable Next Reassessment. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = bEnableReassessmentSpringArmLength))
	float ReassessmentFocusRange = 2000.f;

public:
	UFUNCTION(BlueprintCallable)
	void AddTargetArmLength(float InValue);

	UFUNCTION(BlueprintCallable)
	void SetTargetArmLength(float InValue);

protected:
	bool bLastReassessmentResult = false;
	float DesiredArmLength = 0.f;
	bool NeedReassessment() const;
	void UpdateTargetArmLength(float DeltaTime);
};
