// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/PawnInputMovementInterface.h"
#include "PawnInputMovementComponent.generated.h"

UENUM(BlueprintType)
enum class ECameraRig : uint8
{
	InValid,
	ThirdPerson,
	FirstPerson,
	OverShoulderLeft,
	OverShoulderRight,
	TopDown,
	SideScroller,
	Target
};


/**
 * 对接增强输入，提供简单运动接口
 */
UCLASS(ClassGroup=(GenericFramework), meta=(BlueprintSpawnableComponent), MinimalAPI)
class UPawnInputMovementComponent : public UActorComponent, public IPawnInputMovementInterface
{
	GENERATED_BODY()

public:
	UPawnInputMovementComponent();
	virtual void BeginPlay() override;

	/* IPawnInputMovementInterface */
public:
	virtual void AddLocation_Implementation(FVector2D InValue) override;
	virtual void AddRotation_Implementation(FVector2D InValue) override;
	virtual void AddZoom_Implementation(float InValue) override;
	virtual void SetLocation_Implementation(FVector InValue) override;
	virtual void SetRotation_Implementation(FRotator InValue) override;
	virtual void SetZoom_Implementation(float InValue) override;

	UFUNCTION(BlueprintPure)
	virtual FVector GetLocation() override;

	UFUNCTION(BlueprintPure)
	virtual FRotator GetRotation() override;

	UFUNCTION(BlueprintPure)
	virtual float GetZoom() override;

	UFUNCTION(BlueprintPure)
	virtual float GetMovementBaseSpeed() override;
	
	UFUNCTION(BlueprintPure)
	virtual float GetMovementSpeedRate() override;

	UFUNCTION(BlueprintPure)
	virtual float GetRotationSpeedRate() override;

	UFUNCTION(BlueprintPure)
	virtual float GetZoomSpeedRate() override;

	/* UPawnInputMovementComponent */
public:
	UFUNCTION(BlueprintPure)
	ECameraRig GetActiveCameraRig();

	UFUNCTION(BlueprintCallable)
	void SetActiveCameraRig(ECameraRig InCameraRig);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0, UIMin = 0))
	float MovementBaseSpeed = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0, UIMin = 0))
	float MovementSpeedRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0, UIMin = 0))
	float RotationSpeedRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0, UIMin = 0))
	float ZoomSpeedRate = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSet<ECameraRig> CameraRigSet;

private:
	ECameraRig ActiveCameraRig = ECameraRig::InValid;
};
