// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "GameFramework/Actor.h"
#include "CameraPointBase.generated.h"

class USpringArmComponent;
class USphereComponent;
class UCameraComponent;
class UCameraSwitchMethod;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Camera);

UCLASS(Abstract, HideCategories=(Object,Actor,Collision,Physics,Networking,Input,LevelInstance,Cooking,HLOD,Replication), MinimalAPI)
class ACameraPointBase : public AActor
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
	CAMERASYSTEM_API UCameraComponent* GetCameraComponent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	CAMERASYSTEM_API void SetCameraComponent(UCameraComponent* InCameraComponent);

	/* Refresh The Camera Focus Point */
	UFUNCTION(BlueprintCallable)
	CAMERASYSTEM_API void RefreshFocus();

public:
	DECLARE_EVENT_OneParam(ACameraPointBase, FCameraPointDelegate, ACameraPointBase*)

	CAMERASYSTEM_API inline static FCameraPointDelegate OnCameraPointRegister;
	CAMERASYSTEM_API inline static FCameraPointDelegate OnCameraPointUnRegister;

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
