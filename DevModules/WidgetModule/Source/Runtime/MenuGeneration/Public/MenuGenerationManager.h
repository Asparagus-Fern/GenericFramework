// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/TickableInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "MenuGenerationManager.generated.h"

class UMenuCollection;

/**
 * 
 */
UCLASS()
class MENUGENERATION_API UMenuGenerationManager : public UWorldSubsystem, public FTickableInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

public:
	UMenuCollection* RegisterMenuCollection(TSubclassOf<UMenuCollection> InCollectionClass, bool InActived = true);
	bool RegisterMenuCollection(UMenuCollection* InCollection, bool InActived = true);
	bool UnRegisterMenuCollection(UMenuCollection* InCollection);

protected:
	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<TObjectPtr<UMenuCollection>> MenuCollections;
};
