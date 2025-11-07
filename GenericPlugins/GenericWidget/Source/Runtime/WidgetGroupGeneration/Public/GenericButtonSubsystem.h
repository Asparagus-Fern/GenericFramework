// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WidgetType.h"
#include "Subsystem/GenericWorldSubsystem.h"
#include "GenericButtonSubsystem.generated.h"

class UGenericButtonCollection;

/**
 * Manage Button Collection's Register/UnRegister
 */
UCLASS(MinimalAPI)
class UGenericButtonSubsystem : public UGenericWorldSubsystem
{
	GENERATED_BODY()

public:
	static WIDGETGROUPGENERATION_API UGenericButtonSubsystem* Get(const UObject* WorldContextObject);

public:
	WIDGETGROUPGENERATION_API UGenericButtonCollection* RegisterButtonCollection(APlayerController* Player, TSubclassOf<UGenericButtonCollection> InCollectionClass, bool InActived = true);
	WIDGETGROUPGENERATION_API bool UnRegisterButtonCollection(UGenericButtonCollection* InCollection);

	WIDGETGROUPGENERATION_API bool IsButtonCollectionRegistered(UGenericButtonCollection* InCollection) const;

	WIDGETGROUPGENERATION_API TArray<UGenericButtonCollection*> GetAllButtonCollection() { return Collections; }
	WIDGETGROUPGENERATION_API UGenericButtonCollection* GetButtonCollection(FGameplayTag InRootButtonTag);

private:
	UPROPERTY()
	TArray<TObjectPtr<UGenericButtonCollection>> Collections;
};
