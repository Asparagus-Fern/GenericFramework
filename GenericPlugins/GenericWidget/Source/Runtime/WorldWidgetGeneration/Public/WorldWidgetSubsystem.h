// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystem/GenericWorldSubsystem.h"
#include "WorldWidgetSubsystem.generated.h"

class UWorldWidgetComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnWorldWidgetComponentRegister, UWorldWidgetComponent*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnWorldWidgetComponentRegister, UWorldWidgetComponent*, InWorldWidgetComponent);

DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate_OnWorldWidgetComponentActiveStateChanged, UWorldWidgetComponent*, bool);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBPDelegate_OnWorldWidgetComponentActiveStateChanged, UWorldWidgetComponent*, InWorldWidgetComponent, bool, IsActive);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnWorldWidgetComponentUnRegister, UWorldWidgetComponent*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnWorldWidgetComponentUnRegister, UWorldWidgetComponent*, InWorldWidgetComponent);

/**
 * 
 */
UCLASS(MinimalAPI)
class UWorldWidgetSubsystem : public UGenericWorldSubsystem
{
	GENERATED_BODY()

public:
	static WORLDWIDGETGENERATION_API UWorldWidgetSubsystem* Get(const UObject* WorldContextObject);
	WORLDWIDGETGENERATION_API virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	WORLDWIDGETGENERATION_API virtual void Deinitialize() override;

	/* UWorldGenericWidgetSubsystem */
protected:
	WORLDWIDGETGENERATION_API virtual void RegisterWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent);
	WORLDWIDGETGENERATION_API virtual void UnRegisterWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent);

public:
	WORLDWIDGETGENERATION_API TArray<UWorldWidgetComponent*> GetWorldWidgetComponents() { return WorldWidgetComponents; }

	WORLDWIDGETGENERATION_API TArray<UWorldWidgetComponent*> GetWorldWidgetComponents2D();

	WORLDWIDGETGENERATION_API TArray<UWorldWidgetComponent*> GetWorldWidgetComponents3D();

	WORLDWIDGETGENERATION_API UWorldWidgetComponent* FindWorldWidgetComponent(FGameplayTag WorldWidgetTag);

	WORLDWIDGETGENERATION_API TArray<UWorldWidgetComponent*> FindWorldWidgetComponents(FGameplayTag WorldWidgetTag);

public:
	WORLDWIDGETGENERATION_API inline static FDelegate_OnWorldWidgetComponentRegister Delegate_OnWorldWidgetComponentRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnWorldWidgetComponentRegister BPDelegate_OnWorldWidgetComponentRegister;

	WORLDWIDGETGENERATION_API inline static FDelegate_OnWorldWidgetComponentActiveStateChanged Delegate_OnWorldWidgetComponentActiveStateChanged;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnWorldWidgetComponentActiveStateChanged BPDelegate_OnWorldWidgetComponentActiveStateChanged;

	WORLDWIDGETGENERATION_API inline static FDelegate_OnWorldWidgetComponentUnRegister Delegate_OnWorldWidgetComponentUnRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnWorldWidgetComponentUnRegister BPDelegate_OnWorldWidgetComponentUnRegister;

protected:
	UPROPERTY(Transient)
	TArray<UWorldWidgetComponent*> WorldWidgetComponents;
};
