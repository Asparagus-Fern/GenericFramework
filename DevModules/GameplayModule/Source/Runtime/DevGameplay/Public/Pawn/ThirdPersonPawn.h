// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/GenericPawn.h"
#include "ThirdPersonPawn.generated.h"

class UCameraComponent;
class UPawnSpringArmComponent;
class UCameraSwitchMethod;

UCLASS()
class DEVGAMEPLAY_API AThirdPersonPawn : public AGenericPawn
{
	GENERATED_BODY()

public:
	AThirdPersonPawn(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPawnSpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Transient)
	UCameraComponent* DuplicateCameraComponent = nullptr;

	/* IPawnInputMovementInterface */
public:
	virtual void AddLocation_Implementation(FVector2D InValue) override;
	virtual void AddRotation_Implementation(FVector2D InValue) override;
	virtual void AddZoom_Implementation(float InValue) override;
	virtual void SetLocation_Implementation(FVector InValue) override;
	virtual void SetRotation_Implementation(FRotator InValue) override;
	virtual void SetZoom_Implementation(float InValue) override;
	virtual FVector GetLocation() override;
	virtual FRotator GetRotation() override;
	virtual float GetZoom() override;

	/* AThirdPersonPawn */
protected:
	virtual void OnSwitchCameraBegin(UCameraSwitchMethod* InCameraHandle);
	virtual void OnSwitchCameraFinish(UCameraSwitchMethod* InCameraHandle);

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UCameraComponent* GetActiveCameraComponent();
};
