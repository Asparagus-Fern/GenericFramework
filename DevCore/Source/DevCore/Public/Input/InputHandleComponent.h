// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputType.h"
#include "Components/ActorComponent.h"
#include "InputHandleComponent.generated.h"


class UInputHandle;

UCLASS(ClassGroup=(DevPlugin), meta=(BlueprintSpawnableComponent))
class DEVCORE_API UInputHandleComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInputHandleComponent();
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FEnhanceInputMappingContext> EnhanceInputMappingContexts;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UInputHandle>> InputHandleClasses;

public:
	UPROPERTY(Transient, BlueprintReadOnly)
	TArray<UInputHandle*> InputHandles;

public:
	void GenerateInputHandles();
};
