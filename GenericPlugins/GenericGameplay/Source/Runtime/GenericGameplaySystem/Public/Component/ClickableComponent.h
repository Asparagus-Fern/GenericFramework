// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClickableComponent.generated.h"


UCLASS(ClassGroup=(GenericFramework), meta=(BlueprintSpawnableComponent))
class GENERICGAMEPLAYSYSTEM_API UClickableComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UClickableComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
