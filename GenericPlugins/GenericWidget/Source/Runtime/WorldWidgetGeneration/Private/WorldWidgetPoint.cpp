// Copyright ChenTaiye 2025. All Rights Reserved.


#include "WorldWidgetPoint.h"

#include "WorldWidgetComponent.h"

AWorldWidgetPoint::AWorldWidgetPoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	WorldWidgetComponent = CreateDefaultSubobject<UWorldWidgetComponent>("WorldWidgetComponent");
	RootComponent = WorldWidgetComponent;
}