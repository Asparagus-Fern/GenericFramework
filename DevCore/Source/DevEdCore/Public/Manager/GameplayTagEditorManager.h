// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "Interface/ManagerInterface.h"
#include "GameplayTagEditorManager.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UGameplayTagEditorManager final : public UEditorSubsystem, public FManagerInterface
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};
