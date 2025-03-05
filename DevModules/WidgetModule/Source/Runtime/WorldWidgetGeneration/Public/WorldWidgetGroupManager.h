// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldWidgetGroupManager.generated.h"

class UWorldWidgetComponent;
class UInteractableWidgetEntityGroup;

/**
 * 
 */
UCLASS(MinimalAPI)
class UWorldWidgetGroupManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

public:
	WORLDWIDGETGENERATION_API virtual UInteractableWidgetEntityGroup* GetWorldWidgetGroup(FGameplayTag InGroupTag);

protected:
	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UInteractableWidgetEntityGroup>> WorldWidgetGroupMapping;

	void OnWorldWidgetComponentActiveStateChanged(UWorldWidgetComponent* InWorldWidgetComponent, bool IsActive);
};
