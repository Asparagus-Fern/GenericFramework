// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_EditorScene.generated.h"

/**
 * 
 */
UCLASS()
class DEVEDCORE_API UBPFunctions_EditorScene : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static TArray<AActor*> GetSelectedActors();
	static TArray<UActorComponent*> GetSelectedComponents();

	static void SelectNone();
	static void SelectActor(AActor* InActor, bool bInSelected);
	static void SelectActors(TArray<AActor*> InActors, bool bInSelected);
	static void SelectComponent(UActorComponent* InComponent, bool bInSelected);
	static void SelectComponents(TArray<UActorComponent*> InComponents, bool bInSelected);

	static void RefreshSelection();
};
