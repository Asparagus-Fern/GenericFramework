// Copyright ChenTaiye 2025. All Rights Reserved.

#include "WorldWidgetPoint.h"

#include "WorldWidgetComponent.h"

AWorldWidgetPoint::AWorldWidgetPoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = SceneComponent;

	WorldWidgetComponent = CreateDefaultSubobject<UWorldWidgetComponent>("WorldWidgetComponent");
	WorldWidgetComponent->SetupAttachment(SceneComponent);
}
