// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "BackpackManager.generated.h"

class IBackpackItemInterface;

/**
 * 
 */
UCLASS()
class BACKPACKSYSTEM_API UBackpackManager : public ULocalPlayerSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	void RegisterBackpackItem(IBackpackItemInterface* InBackpackItemInterface);
	void UnRegisterBackpackItem(IBackpackItemInterface* InBackpackItemInterface);

protected:
	TArray<IBackpackItemInterface*> BackpackItemInterfaces;
};
