// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "GameFramework/Actor.h"
#include "WorldWidgetPoint.generated.h"

class UWorldWidgetComponent;
class UGenericWidget;


UCLASS(HideCategories=(Object,Collision,Physics,Networking,Input,LevelInstance,Cooking,HLOD,Replication), MinimalAPI)
class AWorldWidgetPoint : public AActor
{
	GENERATED_BODY()

public:
	AWorldWidgetPoint(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWorldWidgetComponent* WorldWidgetComponent = nullptr;
};
