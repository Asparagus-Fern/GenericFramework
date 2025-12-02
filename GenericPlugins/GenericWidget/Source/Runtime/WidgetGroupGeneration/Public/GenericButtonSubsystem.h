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
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

public:
	WIDGETGROUPGENERATION_API UGenericButtonCollection* RegisterButtonCollection(APlayerController* Player, TSubclassOf<UGenericButtonCollection> InCollectionClass, bool InActived = true);
	WIDGETGROUPGENERATION_API bool UnRegisterButtonCollection(UGenericButtonCollection* InCollection);
	WIDGETGROUPGENERATION_API void UnRegisterAllButtonCollection();

	WIDGETGROUPGENERATION_API bool IsButtonCollectionRegistered(FGameplayTag InRootButtonTag);
	WIDGETGROUPGENERATION_API bool IsButtonCollectionRegistered(UGenericButtonCollection* InCollection) const;

	WIDGETGROUPGENERATION_API TArray<UGenericButtonCollection*> GetAllButtonCollection();
	WIDGETGROUPGENERATION_API UGenericButtonCollection* GetButtonCollection(FGameplayTag InRootButtonTag);
	WIDGETGROUPGENERATION_API TArray<UGenericButtonCollection*> GetButtonCollections(const TArray<FGameplayTag>& InRootButtonTags);

private:
	UPROPERTY()
	TArray<TObjectPtr<UGenericButtonCollection>> Collections;
};
