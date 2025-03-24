// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Manager/TickableInternalManager.h"
#include "WorldWidgetManager.generated.h"

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
UCLASS()
class WORLDWIDGETGENERATION_API UWorldWidgetManager : public UWorldSubsystem, public FTickableInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* UWorldWidgetManager */
protected:
	virtual void RegisterWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent);

	virtual void UnRegisterWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent);

public:
	TArray<UWorldWidgetComponent*> GetWorldWidgetComponents() { return WorldWidgetComponents; }

	TArray<UWorldWidgetComponent*> GetWorldWidgetComponents2D();

	TArray<UWorldWidgetComponent*> GetWorldWidgetComponents3D();

	UWorldWidgetComponent* FindWorldWidgetComponent(FGameplayTag WorldWidgetTag);

	TArray<UWorldWidgetComponent*> FindWorldWidgetComponents(FGameplayTag WorldWidgetTag);

public:
	inline static FDelegate_OnWorldWidgetComponentRegister Delegate_OnWorldWidgetComponentRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnWorldWidgetComponentRegister BPDelegate_OnWorldWidgetComponentRegister;

	inline static FDelegate_OnWorldWidgetComponentActiveStateChanged Delegate_OnWorldWidgetComponentActiveStateChanged;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnWorldWidgetComponentActiveStateChanged BPDelegate_OnWorldWidgetComponentActiveStateChanged;

	inline static FDelegate_OnWorldWidgetComponentUnRegister Delegate_OnWorldWidgetComponentUnRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnWorldWidgetComponentUnRegister BPDelegate_OnWorldWidgetComponentUnRegister;

protected:
	UPROPERTY(Transient)
	TArray<UWorldWidgetComponent*> WorldWidgetComponents;
};
