// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreInternalManager.h"
#include "CharacterManager.generated.h"

class ADevCharacter;
/**
 * 
 */
UCLASS(MinimalAPI)
class UCharacterManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* UCharacterManager */
protected:
	UPROPERTY(Transient)
	TArray<ADevCharacter*> Characters;

protected:
	void RegisterCharacter(ADevCharacter* Character);
	void UnRegisterCharacter(ADevCharacter* Character);
};
