// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWidgetPoint.h"

#include "WorldWidgetComponent.h"

AWorldWidgetPoint::AWorldWidgetPoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	WorldWidgetComponent = CreateDefaultSubobject<UWorldWidgetComponent>("WorldWidgetComponent");
	RootComponent = WorldWidgetComponent;
}