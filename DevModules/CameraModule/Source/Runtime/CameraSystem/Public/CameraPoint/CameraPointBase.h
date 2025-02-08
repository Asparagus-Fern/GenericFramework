// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "GameFramework/Actor.h"
#include "CameraPointBase.generated.h"

class USpringArmComponent;
class USphereComponent;
class UCameraComponent;
class UCameraHandle;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Camera);

UCLASS(Abstract, HideCategories=(Object,Actor,Collision,Physics,Networking,Input,LevelInstance,Cooking,HLOD,Replication))
class CAMERASYSTEM_API ACameraPointBase : public AActor
{
	GENERATED_BODY()

public:
	ACameraPointBase(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Camera"), Category="Camera Point")
	FGameplayTag CameraTag;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> SceneComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent = nullptr;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	UCameraComponent* GetCameraComponent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetCameraComponent(UCameraComponent* InCameraComponent);

public:
	DECLARE_EVENT_OneParam(ACameraPointBase, FCameraPointDelegate, ACameraPointBase*)

	static FCameraPointDelegate OnCameraPointRegister;
	static FCameraPointDelegate OnCameraPointUnRegister;

#if WITH_EDITOR

public:
#if WITH_EDITORONLY_DATA
	/* 用于对接现有的CameraActor，将拷贝该CameraActor所有属性到本相机，包括位置旋转FOV等 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera Point (Editor)")
	ACameraActor* CameraActorLink = nullptr;
#endif

public:
	/* Copy Current Level Viewport Location And Rotation To Self */
	UFUNCTION(CallInEditor, Category="Camera Point (Editor)")
	void CopyFromViewportCamera();

	/* Refresh The Camera Focus Point */
	UFUNCTION(CallInEditor, Category="Camera Point (Editor)")
	void RefreshFocus();

	/* Toggle To Lock Camera Movement */
	UFUNCTION(CallInEditor, Category="Camera Point (Editor)")
	void ToggleLock();

	UFUNCTION(CallInEditor, Category="Camera Point (Editor)")
	void PilotCamera();

	UFUNCTION(CallInEditor, Category="Camera Point (Editor)")
	void EjectPilotCamera();

	UFUNCTION(BlueprintCallable)
	void DuplicateFromCameraActor(ACameraActor* InCameraActor);

	UFUNCTION(BlueprintCallable)
	void DuplicateFromCameraComponent(UCameraComponent* InCameraComponent);

#endif
};
