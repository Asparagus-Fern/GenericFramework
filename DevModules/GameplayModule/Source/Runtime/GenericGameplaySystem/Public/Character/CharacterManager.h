// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interface/ManagerInterface.h"
#include "CharacterManager.generated.h"

class AGenericCharacter;
/**
 * 
 */
UCLASS(MinimalAPI)
class UCharacterManager : public UWorldSubsystem, public FManagerInterface
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
	TArray<AGenericCharacter*> Characters;

protected:
	void RegisterCharacter(AGenericCharacter* Character);
	void UnRegisterCharacter(AGenericCharacter* Character);
};
