// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Manager/TickableInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "MenuGenerationManager.generated.h"

class UMenuCollection;

/**
 * 
 */
UCLASS(MinimalAPI)
class UMenuGenerationManager : public UWorldSubsystem, public FTickableInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

public:
	MENUGENERATION_API UMenuCollection* RegisterMenuCollection(TSubclassOf<UMenuCollection> InCollectionClass, bool InActived = true);
	MENUGENERATION_API bool RegisterMenuCollection(UMenuCollection* InCollection, bool InActived = true);
	MENUGENERATION_API bool UnRegisterMenuCollection(UMenuCollection* InCollection);

protected:
	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<TObjectPtr<UMenuCollection>> MenuCollections;
};
