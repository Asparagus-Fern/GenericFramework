// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "InteractableWidgetEntityGroupManager.generated.h"

class UInteractableWidgetEntity;
class UInteractableWidgetEntityGroup;

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnEntityGroupRegister, UInteractableWidgetEntityGroup*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnEntityGroupRegister, UInteractableWidgetEntityGroup*, InEntityGroup);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnEntityGroupUnRegister, UInteractableWidgetEntityGroup*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnEntityGroupUnRegister, UInteractableWidgetEntityGroup*, InEntityGroup);

/**
 * 管理可交互UI的分组
 */
UCLASS(MinimalAPI)
class UInteractableWidgetEntityGroupManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

public:
	INTERACTABLEWIDGETGENERATION_API UInteractableWidgetEntityGroup* RegisterEntityGroup();
	INTERACTABLEWIDGETGENERATION_API UInteractableWidgetEntityGroup* RegisterEntityGroup(TArray<UInteractableWidgetEntity*> InEntities);

	INTERACTABLEWIDGETGENERATION_API void UnRegisterEntityGroup(TArray<UInteractableWidgetEntityGroup*> InEntityGroups);
	INTERACTABLEWIDGETGENERATION_API void UnRegisterEntityGroup(UInteractableWidgetEntityGroup* InEntityGroup);

public:
	inline static FDelegate_OnEntityGroupRegister Delegate_OnEntityGroupRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnEntityGroupRegister BPDelegate_OnEntityGroupRegister;

	inline static FDelegate_OnEntityGroupUnRegister Delegate_OnEntityGroupUnRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnEntityGroupUnRegister BPDelegate_OnEntityGroupUnRegister;

public:
	TArray<TObjectPtr<UInteractableWidgetEntityGroup>> GetInteractableWidgetEntityGroups() const { return InteractableWidgetEntityGroups; }

protected:
	UPROPERTY(Transient)
	TArray<TObjectPtr<UInteractableWidgetEntityGroup>> InteractableWidgetEntityGroups;
};
