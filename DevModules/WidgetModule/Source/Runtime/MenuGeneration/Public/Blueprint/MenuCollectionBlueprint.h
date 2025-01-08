// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Blueprint.h"
#include "MenuCollectionBlueprint.generated.h"

class UMenuCollectionBlueprintGeneratedClass;

/**
 * 
 */
UCLASS()
class MENUGENERATION_API UMenuCollectionBlueprint : public UBlueprint
{
	GENERATED_BODY()

public:
	UMenuCollectionBlueprint();

#if WITH_EDITOR
	// UBlueprint
	virtual bool SupportedByDefaultBlueprintFactory() const override { return false; }
	virtual UClass* GetBlueprintClass() const override;
	virtual void GetReparentingRules(TSet<const UClass*>& AllowedChildrenOfClasses, TSet<const UClass*>& DisallowedChildrenOfClasses) const override;
	// ~UBlueprint
#endif // WITH_EDITOR

	UMenuCollectionBlueprintGeneratedClass* GetGeneratedClass() const;
};
