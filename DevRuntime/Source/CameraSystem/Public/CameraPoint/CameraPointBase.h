// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "CameraPointBase.generated.h"

class UCameraComponent;
class UCameraHandle;

UCLASS(Abstract, HideCategories=(Object,Actor,Collision,Physics,Networking,Input,LevelInstance,Cooking,HLOD,Replication))
class CAMERASYSTEM_API ACameraPointBase : public AActor
{
	GENERATED_BODY()

public:
	ACameraPointBase();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Camera"), Category="Camera Point")
	FGameplayTag CameraTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category="Camera Point")
	UCameraHandle* CameraHandle;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	UCameraComponent* GetCameraComponent();

#if WITH_EDITOR

public:
	/* 从当前视口拷贝位置与旋转到该相机 */
	UFUNCTION(CallInEditor, BlueprintNativeEvent, Category="Camera Point (Editor)")
	void CopyFromViewportCamera();

	UFUNCTION(CallInEditor, BlueprintNativeEvent, Category="Camera Point (Editor)")
	void PilotCamera();

	UFUNCTION(CallInEditor, BlueprintNativeEvent, Category="Camera Point (Editor)")
	void StopPilotCamera();

#endif
};
