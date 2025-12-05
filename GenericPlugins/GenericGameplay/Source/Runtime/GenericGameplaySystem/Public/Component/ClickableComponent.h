// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "ClickableComponent.generated.h"


UCLASS(ClassGroup=(GenericFramework), meta=(BlueprintSpawnableComponent), MinimalAPI)
class UClickableComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UClickableComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UFUNCTION(BlueprintCallable)
	GENERICGAMEPLAYSYSTEM_API void AddClickableStaticMesh(AStaticMeshActor* InActor);

	UFUNCTION(BlueprintCallable)
	GENERICGAMEPLAYSYSTEM_API void AddClickablePrimitiveComponent(UPrimitiveComponent* InComponent);

protected:
	UFUNCTION()
	void OnComponentBeginCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnComponentEndCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnComponentClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UFUNCTION()
	void OnComponentReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UFUNCTION()
	void OnComponentInputTouchBegin(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnComponentInputTouchEnd(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnComponentInputTouchEnter(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnComponentInputTouchLeave(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableCursorOverEvent = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableClickedEvent = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableTouchEvent = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableTouchDragEvent = true;

private:
	UPROPERTY()
	TArray<TWeakObjectPtr<UPrimitiveComponent>> BindingComponents;
};
