// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/GenericPawn.h"
#include "ThirdPersonPawn.generated.h"

class UCameraComponent;
class UPawnSpringArmComponent;
class UCameraSwitchMethod;

UCLASS(MinimalAPI)
class AThirdPersonPawn : public AGenericPawn
{
	GENERATED_BODY()

public:
	GENERICGAMEPLAYSYSTEM_API AThirdPersonPawn(const FObjectInitializer& ObjectInitializer);
	GENERICGAMEPLAYSYSTEM_API virtual void BeginPlay() override;
	GENERICGAMEPLAYSYSTEM_API virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	GENERICGAMEPLAYSYSTEM_API virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPawnSpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Transient)
	UCameraComponent* DuplicateCameraComponent = nullptr;

	/* IPawnInputMovementInterface */
public:
	GENERICGAMEPLAYSYSTEM_API virtual void AddLocation_Implementation(FVector2D InValue) override;
	GENERICGAMEPLAYSYSTEM_API virtual void AddRotation_Implementation(FVector2D InValue) override;
	GENERICGAMEPLAYSYSTEM_API virtual void AddZoom_Implementation(float InValue) override;
	GENERICGAMEPLAYSYSTEM_API virtual void SetLocation_Implementation(FVector InValue) override;
	GENERICGAMEPLAYSYSTEM_API virtual void SetRotation_Implementation(FRotator InValue) override;
	GENERICGAMEPLAYSYSTEM_API virtual void SetZoom_Implementation(float InValue) override;
	GENERICGAMEPLAYSYSTEM_API virtual FVector GetLocation() override;
	GENERICGAMEPLAYSYSTEM_API virtual FRotator GetRotation() override;
	GENERICGAMEPLAYSYSTEM_API virtual float GetZoom() override;

	/* AThirdPersonPawn */
protected:
	GENERICGAMEPLAYSYSTEM_API virtual void OnSwitchCameraBegin(UCameraSwitchMethod* InCameraHandle);
	GENERICGAMEPLAYSYSTEM_API virtual void OnSwitchCameraFinish(UCameraSwitchMethod* InCameraHandle);

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UCameraComponent* GetActiveCameraComponent();
};
