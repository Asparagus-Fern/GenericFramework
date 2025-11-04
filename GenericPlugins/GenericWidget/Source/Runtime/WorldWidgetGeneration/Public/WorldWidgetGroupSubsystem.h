// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystem/GenericWorldSubsystem.h"
#include "WorldWidgetGroupSubsystem.generated.h"

class UWorldWidgetComponent;
class UGenericButtonGroup;

/**
 * 
 */
UCLASS(MinimalAPI)
class UWorldWidgetGroupSubsystem : public UGenericWorldSubsystem
{
	GENERATED_BODY()

public:
	static WORLDWIDGETGENERATION_API UWorldWidgetGroupSubsystem* Get(const UObject* WorldContextObject);
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	WORLDWIDGETGENERATION_API virtual UGenericButtonGroup* GetWorldWidgetGroup(FGameplayTag InGroupTag);

protected:
	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UGenericButtonGroup>> WorldWidgetGroupMapping;

	void OnWorldWidgetComponentActiveStateChanged(UWorldWidgetComponent* InWorldWidgetComponent, bool IsActive);
};
