// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WidgetType.h"
#include "Interface/ManagerInterface.h"
#include "Subsystems/WorldSubsystem.h"
#include "GenericButtonManager.generated.h"

class UGenericButtonCollection;

/**
 * Manage Button Collection's Register/UnRegister
 */
UCLASS(MinimalAPI)
class UGenericButtonManager : public UWorldSubsystem, public FManagerInterface
{
	GENERATED_BODY()

public:
	WIDGETGROUPGENERATION_API virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	WIDGETGROUPGENERATION_API virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	WIDGETGROUPGENERATION_API virtual void Deinitialize() override;
	WIDGETGROUPGENERATION_API virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

public:
	WIDGETGROUPGENERATION_API UGenericButtonCollection* RegisterButtonCollection(APlayerController* Player, TSubclassOf<UGenericButtonCollection> InCollectionClass, bool InActived = true);
	WIDGETGROUPGENERATION_API bool UnRegisterButtonCollection(UGenericButtonCollection* InCollection);

	WIDGETGROUPGENERATION_API TArray<TObjectPtr<UGenericButtonCollection>> GetAllCollection() { return Collections; }
	WIDGETGROUPGENERATION_API UGenericButtonCollection* GetButtonCollection(FGameplayTag InRootButtonTag);

private:
	TArray<TObjectPtr<UGenericButtonCollection>> Collections;
};
